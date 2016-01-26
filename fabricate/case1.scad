W = 132.230;

module internal_space(){
  color([.5, .4, .5])intersection()
    {

      rotate(v=[1, 0, 0], a=90)
	linear_extrude(height = 400, center = true, convexity = 10)
	import (file = "proto1/side.dxf");
      color([1, 0, 0])
	translate([0, W/2, 0])
	rotate([0, 0, 1], a=-90)
	linear_extrude(height = 100, center = true, convexity = 10)
	import (file = "proto1/top.dxf");
      color([0, 1, 0])
	translate([0, -W/2, 0]) 
	rotate(v=[0, 0, 1], a=90)rotate(a=90, v=[1, 0, 0])
	linear_extrude(height = 500, center = true, convexity = 10)
	import (file = "proto1/front.dxf");
    }
}

minkowski(){
  sphere(r=3);
  internal_space();
}
