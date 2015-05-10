Guide for main method
Step 1: Buil rules library with attributes
Step 2: User Input (Skip for now)
Step 3: Split building into smaller volumes - roof and rest of building
     - if it's an outside block, add shpw to the active shape list
     Shape should have: 
     	   - float xyz[3]; //coord of its lower left corner
	   - float wdh[3]; // width, depth, height of block
	   - int rc[2]; //block the shape belongs to
	   - char *symbol;
	   - int floor;
	   - Attribute a;
	   - int dir[3]; //front facing direction of shape (for 3D drawings)
Step 4: Put in door, band, cornice
     - put door on random 1st floor shape/ middle of front
     - put band and cornice on first and second floor
     - add all active region to end of active list
     - add all terminal shapes to end of build design
     *** Remember to free parent shape ***
Step 5: Add Window & Roof
     - If Window style for the floor is NULL, pick one and all other windows on the same floor uses the same style
Step 6: Loop through building design and transform/rotate design based on dir 
     of shapes



MISC
Axis: positive x - right; positive y - up; positive z - out of screen
Given a building, lower left front corner is 0,0
Row counts along z axis (dec), column along x (inc), level along y (inc)
Width is column diff (x), Depth is row diff (z), Height is level diff (y)
Given, lower left corner of cube, these are 4 coords of shape (in order, LL, LR, UL, UR) when:
       - r = 0 (front):	  (x,y,z), (x+w, y, z), (x, y+h, z), (x+w, y+h, z)
       - r = max (back):  (x+w, y, z-d), (x,y,z-d), (x+c, y+h, z-d), (x, y+h, z-d) 
       - c = 0 (left):	  (x, y, z-d), (x, y, z), (x, y+h, z-d), (x, y+h, z)
       - c = max (right): (x+w, y, z), (x+w, y, z-d), (x+w, y+h, z), (x+w, y+h, z-d)
