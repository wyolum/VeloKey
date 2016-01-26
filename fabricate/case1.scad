color([.5, .4, .5])intersection()
{

rotate(v=[1, 0, 0], a=90)linear_extrude(height = 400, center = true, convexity = 10)
   import (file = "proto1/side.dxf");
scale([1.27, 1, 1])translate([82, 0, 0])rotate([0, 0, 1], a=-90)color([1, 0, 0])linear_extrude(height = 100, center = true, convexity = 10)
   import (file = "proto1/top.dxf");
 scale([1., 1, 1])translate([0, 0, 31]) rotate(v=[0, 0, 1], a=90)rotate(a=90, v=[1, 0, 0])color([0, 1, 0])linear_extrude(height = 500, center = true, convexity = 10)
   import (file = "proto1/front.dxf");
}
