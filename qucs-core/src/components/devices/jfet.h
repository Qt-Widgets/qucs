/*
 * jfet.h - jfet class definitions
 *
 * Copyright (C) 2004, 2005 Stefan Jahn <stefan@lkcc.org>
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this package; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.  
 *
 * $Id: jfet.h,v 1.13 2005-12-19 07:55:14 raimi Exp $
 *
 */

#ifndef __JFET_H__
#define __JFET_H__

class jfet : public circuit
{
 public:
  jfet ();
  void calcSP (nr_double_t);
  void calcNoiseSP (nr_double_t);
  void calcDC (void);
  void initDC (void);
  void saveOperatingPoints (void);
  void calcOperatingPoints (void);
  void initAC (void);
  void calcAC (nr_double_t);
  void calcNoiseAC (nr_double_t);
  void initTR (void);
  void calcTR (nr_double_t);

 private:
  matrix calcMatrixY (nr_double_t);
  matrix calcMatrixCy (nr_double_t);
  void initModel (void);

 private:
  nr_double_t UgsPrev;
  nr_double_t UgdPrev;
  nr_double_t ggs, ggd, gm, gds, Ids, Qgs, Qgd;
  circuit * rs;
  circuit * rd;
};

#endif /* __JFET_H__ */
