$fn=30;

span = 3.5;
board_h = 1.65;
bore_d = 1.9;
d = 4.5;
module part(){
  difference(span, bore){
    cylinder(h=span, d=d);
    translate([0, 0, -1])cylinder(h=span + 2, d=bore);
  }
}

part(span=span, bore=2.5);
translate([10, 0, 0])part(span=span, bore_d);



