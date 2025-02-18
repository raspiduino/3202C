/* putmpg.c, block and motion vector encoding routines                      */

/* Copyright (C) 1996, MPEG Software Simulation Group. All Rights Reserved. */

/*
 * Disclaimer of Warranty
 *
 * These software programs are available to the user without any license fee or
 * royalty on an "as is" basis.  The MPEG Software Simulation Group disclaims
 * any and all warranties, whether express, implied, or statuary, including any
 * implied warranties or merchantability or of fitness for a particular
 * purpose.  In no event shall the copyright-holder be liable for any
 * incidental, punitive, or consequential damages of any kind whatsoever
 * arising from the use of these programs.
 *
 * This disclaimer of warranty extends to the user of these programs and user's
 * customers, employees, agents, transferees, successors, and assigns.
 *
 * The MPEG Software Simulation Group does not represent or warrant that the
 * programs furnished hereunder are free of infringement of any third-party
 * patents.
 *
 * Commercial implementations of MPEG-1 and MPEG-2 video, including shareware,
 * are subject to royalty fees to patent holders.  Many of these patents are
 * general enough such that they are unavoidable regardless of implementation
 * design.
 *
 */

#include "global.h"

/* generate variable length codes for an intra-coded block (6.2.6, 6.3.17) */
void putintrablk(blk,cc)
short *blk;
int cc;
{
  int n, dct_diff, run, signed_level;

  /* DC coefficient (7.2.1) */
  dct_diff = blk[0] - dc_dct_pred[cc]; /* difference to previous block */
  dc_dct_pred[cc] = blk[0];

  if (cc==0)
    putDClum(dct_diff);
  else
    putDCchrom(dct_diff);

  /* AC coefficients (7.2.2) */
  run = 0;
  for (n=1; n<64; n++)
  {
    /* use appropriate entropy scanning pattern */
    signed_level = blk[(altscan ? alternate_scan : zig_zag_scan)[n]];
    if (signed_level!=0)
    {
      putAC(run,signed_level,intravlc);
      run = 0;
    }
    else
      run++; /* count zero coefficients */
  }

  /* End of Block -- normative block punctuation */
  if (intravlc)
    putbits(6,4); /* 0110 (Table B-15) */
  else
    putbits(2,2); /* 10 (Table B-14) */
}

/* generate variable length codes for a non-intra-coded block (6.2.6, 6.3.17) */
void putnonintrablk(blk)
short *blk;
{
  int n, run, signed_level, first;

  run = 0;
  first = 1;

  for (n=0; n<64; n++)
  {
    /* use appropriate entropy scanning pattern */
    signed_level = blk[(altscan ? alternate_scan : zig_zag_scan)[n]];

    if (signed_level!=0)
    {
      if (first)
      {
        /* first coefficient in non-intra block */
        putACfirst(run,signed_level);
        first = 0;
      }
      else
        putAC(run,signed_level,0);

      run = 0;
    }
    else
      run++; /* count zero coefficients */
  }

  /* End of Block -- normative block punctuation  */
  putbits(2,2);
}


