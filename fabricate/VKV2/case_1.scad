inch = 25.4;
WW = 36;
WL = 48.5;
WH = 2;
window_w = 30.;
window_l = 37.5;
window_fw = 35;
window_fl = 47;

module pcb(){
  import("VKV2_pcb.stl");
}

module pcb_outline(){
  hull()difference(){
    pcb();
    translate([-500, -1018, -500])cube(1000);
  }
  xx = 1.6;
  translate([0, -18, -xx])cylinder(d=38.3, h=xx);
}

module ST7735(){
  color([0, 1, 0])translate([0, 0, -7 + 3.4])import("ST7735.stl");
  translate([-WL/2, 1.5, 4.9])cube([WL, WW, WH]);
}

module window(){
  translate([-15.2, 5, -25])cube([35.5, 28.5, 50]);
}

module scroll(color=[.7, .7, .7]){
  $fn=20;
  D = 32;
  H = 6;
  rim = 1;
  rim_h = 1;
  color([.1, .1, .1])cylinder(d=13, h=H-.8);

  color(color)
  difference(){
    union(){
      cylinder(d=D, h=H);
      cylinder(d=D + rim, h=rim_h);
    }
    translate([0, 0, H - .9])cylinder(d1=13, d2=D, h=1);
  }
}

module scrollNSEW(){
  scale([1, 1, .66])scroll(color=[.2, .2, .2]);
}

module assy(){
  translate([ 3.9*inch / 2, 20, 1.8])scroll();
  translate([-3.9*inch / 2, 20, 1.8])scroll();
  translate([-0, -18, 1.8])scrollNSEW();
  pcb_outline();
  ST7735();
}

//assy();
module top(){
  delta = 0;
color([1, 0, 0])  
difference(){
    translate([0, 0, -delta])minkowski(){
    cylinder(h=delta + .4, r=3.2);
    pcb_outline();
  }
  translate([ 3.9*inch/2, 20, -50])cylinder(d=33, h=100, $fn=50);
  translate([-3.9*inch/2, 20, -50])cylinder(d=33, h=100, $fn=50);
  translate([-0, -18, -50])cylinder(d=33, h=100, $fn=50);
  translate([-3.9*inch/2, 20, 1.8])scroll();
  translate([-0, -18, 1.8])scrollNSEW();
  translate([-WL/2, 1.5, 4.9 - 7])cube([WL, WW, WH]);
  window();

translate([25.4, 4.5, -50])cylinder(d=4, h=50, $fn=100);
translate([-25.4, 4.5, -50])cylinder(d=4, h=50, $fn=100);
translate([25.4, 33.6, -50])cylinder(d=4, h=50, $fn=100);
translate([-25.4, 33.6, -50])cylinder(d=4, h=50, $fn=100);
}
}

raise = 5.5;
raise_1 = 8;
translate([0, 0, raise_1])
difference(){
  top();
  translate([0, -18, -2])cylinder(d1=33, d2=45.5, h=4);
}

//translate([ 3.9*inch/2, 20, 3])scroll();
//translate([ -3.9*inch/2, 20, 3])scroll();
//translate([-0, -18, 3])scrollNSEW();
//translate([-0, 0, 0])ST7735();  
//translate([0, 0, 10])import("display.stl");
//translate([0, 0, -6.52])ST7735();  

//translate([0, 0, 0])import("OTS22.stl");


/*
translate([0, 0, raise])
difference(){
  scale([1, 1, 1])top();
  translate([0, -18, 4.7-raise])cylinder(d1=33, d2=50, h=4);
  translate([-WL/2-5, 1.5, 4.9 - 7])cube([WL+10, WW, WH*100]);
}

 */
