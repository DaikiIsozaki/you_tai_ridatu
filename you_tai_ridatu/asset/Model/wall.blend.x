xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Cube {
    FrameTransformMatrix {
       2.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 2.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 2.000000, 0.000000,
       0.000000, 0.000000, 2.000000, 1.000000;;
    }
    Mesh { // Cube mesh
      8;
      -1.000000;-1.000000;-1.000000;,
      -1.000000;-1.000000; 1.000000;,
      -1.000000; 1.000000;-1.000000;,
      -1.000000; 1.000000; 1.000000;,
       1.000000;-1.000000;-1.000000;,
       1.000000;-1.000000; 1.000000;,
       1.000000; 1.000000;-1.000000;,
       1.000000; 1.000000; 1.000000;;
      9;
      4;2,3,1,0;,
      3;2,6,3;,
      3;6,4,7;,
      4;0,1,5,4;,
      4;0,4,6,2;,
      3;7,5,3;,
      3;6,7,3;,
      3;4,5,7;,
      3;5,1,3;;
      MeshNormals { // Cube normals
        9;
        -1.000000;-0.000000; 0.000000;,
         0.000000; 1.000000;-0.000000;,
         1.000000; 0.000000;-0.000000;,
         0.000000;-1.000000; 0.000000;,
         0.000000; 0.000000;-1.000000;,
         0.000000; 0.000000; 1.000000;,
         0.000000; 1.000000;-0.000000;,
         1.000000; 0.000000; 0.000000;,
         0.000000;-0.000000; 1.000000;;
        9;
        4;0,0,0,0;,
        3;1,1,1;,
        3;2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        3;5,5,5;,
        3;6,6,6;,
        3;7,7,7;,
        3;8,8,8;;
      } // End of Cube normals
      MeshMaterialList { // Cube material list
        1;
        9;
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0;
        Material Material_003 {
           0.640000; 0.000000; 0.042550; 1.000000;;
           96.078431;
           0.500000; 0.500000; 0.500000;;
           0.000000; 0.000000; 0.000000;;
        }
      } // End of Cube material list
    } // End of Cube mesh
  } // End of Cube
} // End of Root
