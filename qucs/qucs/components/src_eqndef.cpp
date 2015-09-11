#include "src_eqndef.h"
#include "node.h"
#include "extsimkernels/spicecompat.h"
#include "extsimkernels/verilogawriter.h"


Src_eqndef::Src_eqndef()
{
  Description = QObject::tr("Equation defined (B-type) voltage or current source"); 

  Arcs.append(new Arc(-14,-14, 28, 28,     0, 16*360,QPen(Qt::red,3)));
  Texts.append(new Text(10,-12,"Eqn",Qt::red,10.0,0.0,-1.0));
  Lines.append(new Line(-30,  0,-14,  0,QPen(Qt::darkBlue,2)));
  Lines.append(new Line( 30,  0, 14,  0,QPen(Qt::darkBlue,2)));
  Lines.append(new Line( 18,  5, 18, 11,QPen(Qt::red,1)));
  Lines.append(new Line( 21,  8, 15,  8,QPen(Qt::red,1)));
  Lines.append(new Line(-18,  5,-18, 11,QPen(Qt::black,1)));

  Ports.append(new Port( 30,  0));
  Ports.append(new Port(-30,  0));

  x1 = -30; y1 = -14;
  x2 =  30; y2 =  14;

  tx = x1+4;
  ty = y2+4;
  Model = "B";
  SpiceModel = "B";
  Name  = "B";
  
  Props.append(new Property("VI", "0", true,"Expression"));
  Props.append(new Property("Line 2", "", false,"Expression"));
  Props.append(new Property("Line 3", "", false,"Expression"));
  Props.append(new Property("Line 4", "", false,"Expression"));
  Props.append(new Property("Line 5", "", false,"Expression"));



// Props.append(new Property("V", "0", true,"Expression"));

  rotate();  // fix historical flaw
}

Src_eqndef::~Src_eqndef()
{
}

Component* Src_eqndef::newOne()
{
  return new Src_eqndef();
}

Element* Src_eqndef::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("Equation defined (B-type) voltage or current source");
  BitmapFile = (char *) "src_eqndef";

  if(getNewOne)  return new Src_eqndef();
  return 0;
}

QString Src_eqndef::netlist()
{
    return QString("");
}

QString Src_eqndef::spice_netlist(bool)
{
    QString s = spicecompat::check_refdes(Name,SpiceModel);
    foreach(Port *p1, Ports) {
        QString nam = p1->Connection->Name;
        if (nam=="gnd") nam = "0";
        s += " "+ nam;   // node names
    }
    
    QString VI  = Props.at(0)-> Name;
    QString VI2 = Props.at(0)->Value;
    QString Line_2 = Props.at(1)->Value;
    QString Line_3 = Props.at(2)->Value;
    QString Line_4 = Props.at(3)->Value;
    QString Line_5 = Props.at(4)->Value;

    s += QString(" %1 = %2 \n").arg(VI).arg(VI2);
    if(  Line_2.length() > 0 )   s += QString("%1\n").arg(Line_2);
    if(  Line_3.length() > 0 )   s += QString("%1\n").arg(Line_3);
    if(  Line_4.length() > 0 )   s += QString("%1\n").arg(Line_4);
    if(  Line_5.length() > 0 )   s += QString("%1\n").arg(Line_5);
 
    return s;
}

QString Src_eqndef::va_code()
{
    QString s;
    QString plus = Ports.at(0)->Connection->Name;
    QString minus = Ports.at(1)->Connection->Name;
    QString Src;
    if (Props.at(0)->Name=="I") Src = vacompat::normalize_current(plus,minus,true);
    else Src = vacompat::normalize_voltage(plus,minus); // Voltage contribution is reserved for future
    // B-source may be polar
    if (plus=="gnd") s = QString(" %1 <+ -(%2); // %3 source\n").arg(Src).arg(Props.at(0)->Value).arg(Name);
    else s = QString(" %1 <+ %2; // %3 source\n").arg(Src).arg(Props.at(0)->Value).arg(Name);
    return s;
}
