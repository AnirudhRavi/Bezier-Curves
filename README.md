**Program**: Set of Programs to create Bezier Curves (using De Casteljau's and Bernstein Bezier algorithms) along with a generating a surface of revolution given a curve 

**Author**: Anirudh Ravi

**About**:

These programs are written in either C++ or C. It uses both Bernstein Bezier and De Casteljau's to create a Bezier curve given a set of points input through an OpenGL interface. One of the programs creates a surface of revolution given a Bezier Curve.

**Program 1: DeCasteljau.cpp**

Implemented the de Castlejau algorithm for evaluating an entire 2D Bezier curve.

**Program 2: Bernstein.cpp**

Implemented the Bernstein form of 2D Bezier curve for any degree. If the user enters (n + 1) points then the curve will be of degree n. 

**Program 3: EditableBezier.cpp**

Makes the Bezier curve editable in the sense that if one wants they can drag any control point of the curve and the curve gets updated automatically.

**Program 4: BezierSurfaceRevolution.c**

Samples the curves generated using Bernstein Bezier approach at a uniform interval of size 0.1. Makes a surface of revolution using these sampled points on the curve. The surface of revolution will be a polygonal mesh. This polygonal mesh is stored in an OFF file format and can be viewed using a viewer such as Geomview/ Meshview/Paraview.

**Executing**:

gcc ProgramName -lGL -lGLU -lglut -lm -o ExecutableName

./ExecutableName (Execute)
