/* REXX */

CALL IMPORT FSSAPI
ADDRESS FSS

CALL FSSINIT

CENTER=FSSWIDTH()%2
LAST=FSSHEIGHT()

CALL FSSTITLE 'BREXX/370', #BLUE

CALL FSSTEXT "Specify member name to recompile,",4,CENTER - 16,,#PROT+#WHITE
CALL FSSTEXT "or leave field empty for full rebuid.",5,CENTER - 18,,#PROT+#WHITE

NXT = FSSTEXT(  "Member name"   ,  8, CENTER - 17,   , #PROT+#TURQ)
NXT = FSSTEXT(  "===>"          ,  8, NXT        ,   , #PROT+#HI+#WHITE)
NXT = FSSFIELD( 'MEMBER'        ,  8, NXT        ,  8, #HI+#RED+#USCORE, '')
NXT = FSSTEXT(  "Debug ?"       ,  8, NXT        ,   , #PROT+#TURQ)
NXT = FSSFIELD( 'DEBUG'         ,  8, NXT        ,  1, #HI+#RED+#USCORE, 'N')

CALL FSSCURSOR 'MEMBER'

DO FOREVER
   RCKEY=FSSREFRESH()   /* DISPLAY/REFRESH FORMATTED SCREEN */
   IF RCKEY==#PFK03 | RCKEY==#PFK15 THEN LEAVE
END
CALL FSSCLOSE
