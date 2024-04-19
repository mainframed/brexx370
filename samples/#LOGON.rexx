/* REXX */

/* 1. IMPORT FULL SCREEN SERVICE API */
CALL IMPORT FSSAPI

/* 2. ADDRESS FSS IS MANDATORY */
ADDRESS FSS

/* 3. ENABLE FULL SCREEN MODE */
CALL FSSINIT

VUID=''
VPWD=''
VCMD=''

/* 4. SCREEN DEFINITION  */
CALL FSSTITLE   'BREXX/370',#BLUE
CALL FSSCOMMAND 2,,#RED+#USCORE
CALL FSSFIELD 'MSG'      , 3, 1,40,#PROT+#HI+#RED    ,''

CALL FSSTEXT  "USERID   ",10,19,  ,#PROT+#TURQ
CALL FSSTEXT  "===>"     ,10,28,  ,#PROT+#HI+#GREEN
CALL FSSFIELD 'USERID'   ,10,33, 8                   ,''
CALL FSSTEXT  "PASSWORD ",11,19,  ,#PROT+#TURQ
CALL FSSTEXT  "===>"     ,11,28,  ,#PROT+#HI+#GREEN
CALL FSSFIELD 'PASSWD'   ,11,33, 8,#NON              ,''

CALL FSSTEXT( "PF3=TERMINATE" ,FSSHEIGHT(), 1,  ,#PROT+#HI)

CALL FSSCURSOR 'USERID'

/* 5. KEY HANDLER        */
DO FOREVER
   RCKEY=FSSREFRESH()   /* DISPLAY/REFRESH FORMATTED SCREEN */
   IF RCKEY==#PFK03 | RCKEY==#PFK15 THEN LEAVE
   CALL FSSFSET 'MSG',''
   VUID=FSSFGET(USERID)
   VPWD=FSSFGET(PASSWD)
   VCMD=STRIP(FSSFGET(ZCMD))
   IF VCMD <> '' THEN DO
     CALL FSSFSET 'MSG', VCMD" COULDN'T BE EXECUTED IN THIS DEMO."
   END
   ELSE DO
     IF STRIP(VUID) == '' THEN DO
        CALL FSSFSET 'MSG','PLEASE ENTER USERID'
        CALL FSSCURSOR 'USERID'
     END
     ELSE DO
        IF STRIP(VPWD) <> '' THEN LEAVE
        CALL FSSFSET 'MSG','PLEASE ENTER PASSWORD FOR 'VUID
        CALL FSSCOLOR 'USERID',#YELLOW
        CALL FSSCURSOR 'PASSWD'
     END
   END
END
SAY "GIVEN USERID IS" VUID
SAY "GIVEN PASSWD IS" VPWD
SAY "GIVEN CMD    IS" VCMD
CALL FSSCLOSE
