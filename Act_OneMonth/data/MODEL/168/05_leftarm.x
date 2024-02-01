xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 20;
 9.81242;-0.65711;-2.48377;,
 0.24420;-1.08322;-1.70684;,
 9.63269;-0.20404;-2.48377;,
 0.00000;-0.00467;-1.70684;,
 -1.91482;-1.16840;-0.58309;,
 -1.69063;-1.18346;0.72980;,
 -1.79480;0.54901;-0.58309;,
 -1.62747;0.59857;0.83115;,
 -0.00085;-0.00740;1.74420;,
 0.25948;-1.03371;1.65914;,
 9.78224;0.28033;5.56068;,
 9.80489;-0.68149;5.45782;,
 10.14882;0.73261;0.54908;,
 10.01150;-0.71596;0.44773;,
 10.17369;0.80747;0.00000;,
 9.97517;-0.82531;-0.00000;,
 0.22755;0.73240;-0.59326;,
 0.16483;-1.34027;-0.44774;,
 10.14477;0.72043;-0.59327;,
 10.00791;-0.72676;-0.44773;;
 
 36;
 3;0,1,2;,
 3;1,3,2;,
 3;4,5,6;,
 3;5,7,6;,
 3;8,9,10;,
 3;9,11,10;,
 3;12,13,14;,
 3;13,15,14;,
 3;6,7,14;,
 3;7,12,14;,
 3;13,5,15;,
 3;5,4,15;,
 3;16,17,6;,
 3;17,4,6;,
 3;18,16,14;,
 3;16,6,14;,
 3;15,19,14;,
 3;19,18,14;,
 3;4,17,15;,
 3;15,17,19;,
 3;1,17,3;,
 3;17,16,3;,
 3;18,2,16;,
 3;2,3,16;,
 3;18,19,2;,
 3;19,0,2;,
 3;17,1,19;,
 3;1,0,19;,
 3;10,11,12;,
 3;11,13,12;,
 3;7,8,12;,
 3;8,10,12;,
 3;7,5,8;,
 3;5,9,8;,
 3;11,9,13;,
 3;9,5,13;;
 
 MeshMaterialList {
  1;
  36;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV_168.png";
   }
  }
 }
 MeshNormals {
  49;
  -0.079497;-0.031536;-0.996336;,
  -0.070188;0.294899;-0.952947;,
  -0.080129;-0.024911;-0.996473;,
  -0.061478;0.467070;-0.882081;,
  -0.377140;-0.150866;0.913786;,
  -0.423246;-0.125967;0.897215;,
  -0.364185;-0.107510;0.925101;,
  -0.359323;-0.136869;0.923122;,
  -0.983271;0.068715;0.168692;,
  -0.988575;0.048666;0.142657;,
  0.994052;-0.108888;-0.001830;,
  0.992687;-0.120695;-0.002519;,
  0.032990;-0.037333;-0.998758;,
  0.001338;-0.070077;-0.997541;,
  0.001153;0.955216;-0.295907;,
  0.997502;0.009447;-0.070006;,
  0.994460;-0.104850;0.007530;,
  0.997007;-0.059489;0.049381;,
  -0.834881;-0.001714;0.550428;,
  -0.815519;-0.031906;0.577850;,
  -0.040194;0.904788;0.423962;,
  -0.008420;0.974482;0.224309;,
  -0.021387;0.978941;0.203018;,
  -0.022874;0.964606;0.262701;,
  0.040050;-0.993607;0.105552;,
  0.038765;-0.994496;0.097337;,
  0.045736;-0.998951;0.002295;,
  0.029649;-0.999424;-0.016527;,
  0.064574;-0.004513;-0.997903;,
  -0.008342;0.923312;-0.383960;,
  -0.051644;0.613218;0.788224;,
  0.986954;-0.105562;-0.121570;,
  -0.052577;0.142218;0.988438;,
  0.060911;-0.977252;-0.203148;,
  0.054567;-0.987390;-0.148604;,
  -0.969822;-0.219582;-0.105963;,
  -0.995306;-0.090493;0.034305;,
  -0.983975;0.041943;0.173305;,
  0.001084;0.898226;-0.439533;,
  0.980359;0.131611;-0.146880;,
  0.926815;0.367662;-0.076411;,
  0.051350;-0.991754;-0.117422;,
  0.041368;-0.998416;-0.038126;,
  0.997112;0.015532;0.074337;,
  0.997472;-0.040895;0.058107;,
  -0.030367;0.944550;0.326961;,
  -0.062473;0.994406;0.085172;,
  0.033590;-0.999402;0.008261;,
  0.037603;-0.998459;0.040813;;
  36;
  3;0,2,1;,
  3;2,3,1;,
  3;8,19,9;,
  3;19,18,9;,
  3;5,4,7;,
  3;4,6,7;,
  3;17,16,10;,
  3;16,11,10;,
  3;20,21,22;,
  3;21,23,22;,
  3;24,25,26;,
  3;25,27,26;,
  3;13,12,12;,
  3;12,28,12;,
  3;14,29,22;,
  3;30,20,22;,
  3;11,15,10;,
  3;15,31,10;,
  3;32,32,32;,
  3;26,33,34;,
  3;35,36,36;,
  3;36,37,36;,
  3;14,38,29;,
  3;1,3,29;,
  3;31,15,39;,
  3;15,40,39;,
  3;33,41,34;,
  3;41,42,34;,
  3;43,44,17;,
  3;44,16,17;,
  3;21,45,23;,
  3;45,46,23;,
  3;18,19,5;,
  3;19,4,5;,
  3;47,48,24;,
  3;48,25,24;;
 }
 MeshTextureCoords {
  20;
  0.906219;0.342454;,
  0.621240;0.367372;,
  0.900866;0.315960;,
  0.613966;0.304301;,
  0.556935;0.372354;,
  0.563613;0.373235;,
  0.560510;0.271922;,
  0.565494;0.269024;,
  0.613941;0.304460;,
  0.621695;0.364477;,
  0.905320;0.287634;,
  0.905995;0.343880;,
  0.916239;0.261185;,
  0.912149;0.345896;,
  0.916979;0.256808;,
  0.911067;0.352291;,
  0.620744;0.261198;,
  0.618876;0.382405;,
  0.916118;0.261898;,
  0.912042;0.346527;;
 }
}
