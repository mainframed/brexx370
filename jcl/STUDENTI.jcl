//BRXVSMIN JOB CLASS=A,MSGCLASS=H,REGION=8192K,
//         NOTIFY=&SYSUID
//*
//*RELEASE   SET 'V2R5M3'
//* ... BREXX          Version V2R5M3 Build Date 01. Feb 2024
//* ... INSTALLER DATE 03/02/2024 17:40:28
//* -----------------------------------------------------------------
//* STEP 1 INSERT RECORDS INTO VSAM FILE
//* -----------------------------------------------------------------
//*
//BATCH EXEC RXTSO,BREXX='BREXX',
//         EXEC='@STUDENI',
//         SLIB='BREXX.V2R5M3.SAMPLES'
//SYSPRINT DD  SYSOUT=*,
//             DCB=(RECFM=FBA,LRECL=133,BLKSIZE=133)
//SYSUDUMP DD  SYSOUT=*
//