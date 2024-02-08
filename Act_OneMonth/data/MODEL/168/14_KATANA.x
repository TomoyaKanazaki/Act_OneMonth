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
 120;
 0.14423;27.38013;1.78774;,
 0.00000;29.72679;2.17121;,
 -0.14423;27.38013;1.78774;,
 0.14423;26.41629;1.62370;,
 -0.14423;26.41629;1.62370;,
 0.14423;25.45109;1.47833;,
 -0.14423;25.45109;1.47833;,
 0.14423;24.48633;1.32694;,
 -0.14423;24.48633;1.32694;,
 0.14423;23.52082;1.18581;,
 -0.14423;23.52082;1.18581;,
 0.14423;22.55402;1.06247;,
 -0.14423;22.55402;1.06247;,
 0.14423;21.58738;0.93689;,
 -0.14423;21.58738;0.93689;,
 0.14423;20.61883;0.83744;,
 -0.14423;20.61883;0.83744;,
 0.14423;19.65013;0.74023;,
 -0.14423;19.65013;0.74023;,
 0.14423;18.68111;0.64738;,
 -0.14423;18.68111;0.64738;,
 0.14423;17.71006;0.58231;,
 -0.14423;17.71006;0.58231;,
 0.14423;16.73992;0.50484;,
 -0.14423;16.73992;0.50484;,
 0.14423;15.76742;0.45981;,
 -0.14423;15.76742;0.45981;,
 0.14423;14.79812;0.37083;,
 -0.14423;14.79812;0.37083;,
 0.14423;13.82587;0.32229;,
 -0.14423;13.82587;0.32229;,
 0.14423;12.85189;0.29755;,
 -0.14423;12.85189;0.29755;,
 0.14423;11.87832;0.26715;,
 -0.14423;11.87832;0.26715;,
 0.14423;10.90461;0.23882;,
 -0.14423;10.90461;0.23882;,
 0.14423;9.93018;0.22027;,
 -0.14423;9.93018;0.22027;,
 0.14423;8.95672;0.18846;,
 -0.14423;8.95672;0.18846;,
 0.14423;7.98255;0.16629;,
 -0.14423;7.98255;0.16629;,
 0.14423;7.00587;0.17864;,
 -0.14423;7.00587;0.17864;,
 0.14423;6.02820;0.20472;,
 -0.14423;6.02820;0.20472;,
 0.14423;5.05226;0.20691;,
 -0.14423;5.05226;0.20691;,
 0.14423;4.07481;0.22989;,
 -0.14423;4.07481;0.22989;,
 0.14423;2.68935;0.34313;,
 -0.14423;2.68935;0.34313;,
 0.36702;2.73686;1.13550;,
 -0.36702;2.73686;1.13550;,
 0.36702;2.49791;1.20891;,
 -0.36702;2.49791;1.20891;,
 0.36702;2.36394;0.30179;,
 -0.36702;2.36394;0.30179;,
 0.36702;1.13595;0.38826;,
 -0.36702;1.13595;0.38826;,
 0.36702;0.15787;0.41981;,
 -0.36702;0.15787;0.41981;,
 0.36702;-0.82541;0.52300;,
 -0.36702;-0.82541;0.52300;,
 0.36702;-1.80974;0.64044;,
 -0.36702;-1.80974;0.64044;,
 0.36702;-2.68179;0.64024;,
 -0.36702;-2.68179;0.64024;,
 0.36702;-2.73825;-0.29478;,
 -0.36702;-2.73825;-0.29478;,
 0.36702;-1.73623;-0.36971;,
 -0.36702;-1.73623;-0.36971;,
 0.36702;-0.75191;-0.48714;,
 -0.36702;-0.75191;-0.48714;,
 0.36702;0.23138;-0.59033;,
 -0.36702;0.23138;-0.59033;,
 0.36702;1.20945;-0.62188;,
 -0.36702;1.20945;-0.62188;,
 0.36702;2.29968;-0.75594;,
 -0.36702;2.29968;-0.75594;,
 0.36702;2.29221;-1.73334;,
 -0.36702;2.29221;-1.73334;,
 0.36702;2.58352;-1.71455;,
 -0.36702;2.58352;-1.71455;,
 0.00000;28.57271;1.14641;,
 0.00000;27.46166;0.66733;,
 0.00000;26.49756;0.50691;,
 0.00000;25.53282;0.35514;,
 0.00000;24.56754;0.21098;,
 0.00000;23.60098;0.08422;,
 0.00000;22.63453;-0.04404;,
 0.00000;21.66747;-0.16370;,
 0.00000;20.69808;-0.25153;,
 0.00000;19.72944;-0.34970;,
 0.00000;18.75890;-0.42171;,
 0.00000;17.78948;-0.50906;,
 0.00000;16.81980;-0.59288;,
 0.00000;15.84943;-0.66723;,
 0.00000;14.87636;-0.70438;,
 0.00000;13.90460;-0.75965;,
 0.00000;12.93176;-0.80000;,
 0.00000;11.95827;-0.83142;,
 0.00000;10.98413;-0.85395;,
 0.00000;10.01097;-0.88992;,
 0.00000;9.03599;-0.90087;,
 0.00000;8.06199;-0.92543;,
 0.00000;7.08833;-0.95457;,
 0.00000;6.11079;-0.93026;,
 0.00000;5.13374;-0.91282;,
 0.00000;4.15562;-0.88070;,
 0.00000;2.63520;-0.87162;,
 -0.86976;2.63520;-0.87162;,
 -0.86976;2.29968;-0.75594;,
 -0.86976;2.68935;0.34313;,
 -0.86976;2.36394;0.30179;,
 0.86976;2.63520;-0.87162;,
 0.86976;2.68935;0.34313;,
 0.86976;2.29968;-0.75594;,
 0.86976;2.36394;0.30179;;
 
 236;
 3;0,1,2;,
 3;0,2,3;,
 3;3,2,4;,
 3;3,4,5;,
 3;5,4,6;,
 3;5,6,7;,
 3;7,6,8;,
 3;7,8,9;,
 3;9,8,10;,
 3;9,10,11;,
 3;11,10,12;,
 3;11,12,13;,
 3;13,12,14;,
 3;13,14,15;,
 3;15,14,16;,
 3;15,16,17;,
 3;17,16,18;,
 3;17,18,19;,
 3;19,18,20;,
 3;19,20,21;,
 3;21,20,22;,
 3;21,22,23;,
 3;23,22,24;,
 3;23,24,25;,
 3;25,24,26;,
 3;25,26,27;,
 3;27,26,28;,
 3;27,28,29;,
 3;29,28,30;,
 3;29,30,31;,
 3;31,30,32;,
 3;31,32,33;,
 3;33,32,34;,
 3;33,34,35;,
 3;35,34,36;,
 3;35,36,37;,
 3;37,36,38;,
 3;37,38,39;,
 3;39,38,40;,
 3;39,40,41;,
 3;41,40,42;,
 3;41,42,43;,
 3;43,42,44;,
 3;43,44,45;,
 3;45,44,46;,
 3;45,46,47;,
 3;47,46,48;,
 3;47,48,49;,
 3;49,48,50;,
 3;49,50,51;,
 3;51,50,52;,
 3;53,54,55;,
 3;55,54,56;,
 3;57,58,59;,
 3;59,58,60;,
 3;59,60,61;,
 3;61,60,62;,
 3;61,62,63;,
 3;63,62,64;,
 3;63,64,65;,
 3;65,64,66;,
 3;65,66,67;,
 3;67,66,68;,
 3;67,68,69;,
 3;69,68,70;,
 3;69,70,71;,
 3;71,70,72;,
 3;71,72,73;,
 3;73,72,74;,
 3;73,74,75;,
 3;75,74,76;,
 3;75,76,77;,
 3;77,76,78;,
 3;77,78,79;,
 3;79,78,80;,
 3;81,82,83;,
 3;83,82,84;,
 3;1,85,2;,
 3;2,85,86;,
 3;2,86,4;,
 3;4,86,87;,
 3;4,87,6;,
 3;6,87,88;,
 3;6,88,8;,
 3;8,88,89;,
 3;8,89,10;,
 3;10,89,90;,
 3;10,90,12;,
 3;12,90,91;,
 3;12,91,14;,
 3;14,91,92;,
 3;14,92,16;,
 3;16,92,93;,
 3;16,93,18;,
 3;18,93,94;,
 3;18,94,20;,
 3;20,94,95;,
 3;20,95,22;,
 3;22,95,96;,
 3;22,96,24;,
 3;24,96,97;,
 3;97,98,24;,
 3;24,98,26;,
 3;98,99,26;,
 3;26,99,28;,
 3;99,100,28;,
 3;28,100,30;,
 3;100,101,30;,
 3;30,101,32;,
 3;101,102,32;,
 3;32,102,34;,
 3;102,103,34;,
 3;34,103,36;,
 3;103,104,36;,
 3;36,104,38;,
 3;104,105,38;,
 3;38,105,40;,
 3;105,106,40;,
 3;40,106,42;,
 3;106,107,42;,
 3;42,107,44;,
 3;107,108,44;,
 3;44,108,46;,
 3;108,109,46;,
 3;46,109,48;,
 3;109,110,48;,
 3;48,110,50;,
 3;110,111,50;,
 3;50,111,52;,
 3;112,113,114;,
 3;114,113,115;,
 3;80,78,58;,
 3;58,78,60;,
 3;78,76,60;,
 3;60,76,62;,
 3;76,74,62;,
 3;62,74,64;,
 3;74,72,64;,
 3;64,72,66;,
 3;72,70,66;,
 3;66,70,68;,
 3;1,0,85;,
 3;85,0,86;,
 3;0,3,86;,
 3;86,3,87;,
 3;3,5,87;,
 3;87,5,88;,
 3;5,7,88;,
 3;88,7,89;,
 3;7,9,89;,
 3;89,9,90;,
 3;9,11,90;,
 3;90,11,91;,
 3;11,13,91;,
 3;91,13,92;,
 3;13,15,92;,
 3;92,15,93;,
 3;15,17,93;,
 3;93,17,94;,
 3;17,19,94;,
 3;94,19,95;,
 3;19,21,95;,
 3;95,21,96;,
 3;21,23,96;,
 3;96,23,97;,
 3;97,23,98;,
 3;98,23,25;,
 3;98,25,99;,
 3;99,25,27;,
 3;99,27,100;,
 3;100,27,29;,
 3;100,29,101;,
 3;101,29,31;,
 3;101,31,102;,
 3;102,31,33;,
 3;102,33,103;,
 3;103,33,35;,
 3;103,35,104;,
 3;104,35,37;,
 3;104,37,105;,
 3;105,37,39;,
 3;105,39,106;,
 3;106,39,41;,
 3;106,41,107;,
 3;107,41,43;,
 3;107,43,108;,
 3;108,43,45;,
 3;108,45,109;,
 3;109,45,47;,
 3;109,47,110;,
 3;110,47,49;,
 3;110,49,111;,
 3;111,49,51;,
 3;116,117,118;,
 3;118,117,119;,
 3;79,57,77;,
 3;77,57,59;,
 3;77,59,75;,
 3;75,59,61;,
 3;75,61,73;,
 3;73,61,63;,
 3;73,63,71;,
 3;71,63,65;,
 3;71,65,69;,
 3;69,65,67;,
 3;51,52,53;,
 3;53,52,54;,
 3;58,56,52;,
 3;52,56,54;,
 3;58,57,56;,
 3;56,57,55;,
 3;57,51,55;,
 3;55,51,53;,
 3;79,80,81;,
 3;81,80,82;,
 3;80,111,82;,
 3;82,111,84;,
 3;84,111,83;,
 3;79,81,111;,
 3;111,81,83;,
 3;52,111,114;,
 3;114,111,112;,
 3;111,80,112;,
 3;112,80,113;,
 3;80,58,113;,
 3;113,58,115;,
 3;58,52,115;,
 3;115,52,114;,
 3;111,51,116;,
 3;116,51,117;,
 3;51,57,117;,
 3;117,57,119;,
 3;57,79,119;,
 3;119,79,118;,
 3;79,111,118;,
 3;118,111,116;;
 
 MeshMaterialList {
  1;
  236;
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
    "data\\TEXTURE\\UV_168.jpg";
   }
  }
 }
 MeshNormals {
  219;
  0.000000;-0.161272;0.986910;,
  0.000000;-0.164528;0.986373;,
  0.000000;-0.165613;0.986191;,
  0.000000;-0.161505;0.986872;,
  0.000000;-0.155221;0.987880;,
  0.000000;-0.150963;0.988540;,
  0.000000;-0.152993;0.988227;,
  0.000000;-0.151562;0.988448;,
  0.000000;-0.148099;0.988973;,
  0.000000;-0.138612;0.990347;,
  0.000000;-0.132583;0.991172;,
  0.000000;-0.127310;0.991863;,
  0.000000;-0.128071;0.991765;,
  0.000000;-0.119944;0.992781;,
  0.000000;-0.111047;0.993815;,
  0.000000;-0.101378;0.994848;,
  0.000000;-0.100614;0.994926;,
  0.000000;-0.098360;0.995151;,
  0.000000;-0.096871;0.995297;,
  0.000000;-0.085882;0.996305;,
  0.000000;-0.076374;0.997079;,
  0.000000;-0.071108;0.997469;,
  0.000000;-0.075355;0.997157;,
  0.000000;-0.068494;0.997652;,
  0.000000;-0.057377;0.998353;,
  0.000000;-0.061321;0.998118;,
  0.000000;-0.076378;0.997079;,
  0.000000;-0.077579;0.996986;,
  0.000000;-0.063726;0.997968;,
  0.000000;-0.041709;0.999130;,
  0.000000;-0.033552;0.999437;,
  0.000000;-0.027332;0.999626;,
  0.000000;-0.029271;0.999571;,
  0.000000;-0.030501;0.999535;,
  0.000000;-0.029792;0.999556;,
  0.000000;-0.025733;0.999669;,
  0.000000;-0.022383;0.999749;,
  0.000000;-0.023576;0.999722;,
  0.000000;-0.028118;0.999605;,
  0.000000;-0.029358;0.999569;,
  0.000000;-0.026055;0.999660;,
  0.000000;-0.010955;0.999940;,
  0.000000;0.000845;1.000000;,
  0.000000;0.017318;0.999850;,
  0.000000;0.021993;0.999758;,
  0.000000;0.018527;0.999828;,
  0.000000;0.010385;0.999946;,
  0.000000;0.009331;0.999956;,
  0.000000;0.016418;0.999865;,
  0.000000;0.042839;0.999082;,
  0.000000;0.062166;0.998066;,
  0.000000;0.012359;0.999924;,
  0.000000;-0.057138;0.998366;,
  0.000000;-0.060865;0.998146;,
  0.000000;0.004840;0.999988;,
  0.000000;0.057584;0.998341;,
  0.000000;0.044915;0.998991;,
  0.000000;0.056317;0.998413;,
  0.000000;0.080374;0.996765;,
  0.000000;0.109073;0.994034;,
  0.000000;0.113773;0.993507;,
  0.000000;0.079027;0.996872;,
  0.000000;0.039399;0.999224;,
  0.000000;-0.000229;1.000000;,
  0.000000;-0.000229;1.000000;,
  0.000000;-0.998182;0.060274;,
  0.000000;-0.089220;-0.996012;,
  0.000000;-0.103853;-0.994593;,
  0.000000;-0.113766;-0.993508;,
  0.000000;-0.109070;-0.994034;,
  0.000000;-0.080374;-0.996765;,
  0.000000;-0.056317;-0.998413;,
  0.000000;-0.062232;-0.998062;,
  0.000000;-0.092194;-0.995741;,
  0.000000;-0.190945;-0.981601;,
  0.000000;-0.259246;-0.965811;,
  -0.980515;0.192184;0.040701;,
  -0.991689;-0.002669;-0.128632;,
  -0.991855;-0.002248;-0.127350;,
  -0.991983;-0.002923;-0.126337;,
  -0.991793;-0.000277;-0.127850;,
  -0.991400;0.003397;-0.130825;,
  -0.991479;0.003010;-0.130233;,
  -0.991602;0.002906;-0.129297;,
  -0.991461;0.003876;-0.130346;,
  -0.991515;0.003752;-0.129942;,
  -0.991426;0.004321;-0.130596;,
  -0.991236;0.006523;-0.131940;,
  -0.991433;0.008163;-0.130358;,
  -0.991808;0.006873;-0.127554;,
  -0.991522;0.010559;-0.129508;,
  -0.991456;0.011107;-0.129965;,
  -0.991188;0.010171;-0.132070;,
  -0.991289;0.011850;-0.131167;,
  -0.991388;0.012699;-0.130343;,
  -0.991498;0.013666;-0.129401;,
  -0.991600;0.016520;-0.128282;,
  -0.991579;0.016755;-0.128415;,
  -0.991685;0.018113;-0.127407;,
  -0.991811;0.019502;-0.126215;,
  -0.991780;0.019983;-0.126388;,
  -0.991584;0.031953;-0.125459;,
  -0.992509;0.064102;-0.104007;,
  0.000000;0.293673;0.955906;,
  0.000000;0.064368;-0.997926;,
  -1.000000;0.000000;0.000000;,
  1.000000;-0.000000;0.000000;,
  0.000000;-0.074571;-0.997216;,
  -0.993627;0.074843;-0.084285;,
  -0.992522;0.049900;-0.111404;,
  -0.991760;0.020534;-0.126451;,
  -0.991815;0.019550;-0.126181;,
  -0.991781;0.019079;-0.126517;,
  -0.991622;0.017271;-0.128018;,
  -0.991604;0.016678;-0.128231;,
  -0.991579;0.015271;-0.128601;,
  -0.991442;0.012714;-0.129925;,
  -0.991392;0.012921;-0.130289;,
  -0.991180;0.010422;-0.132108;,
  -0.991307;0.010349;-0.131163;,
  -0.991607;0.009344;-0.128950;,
  -0.991694;0.007605;-0.128394;,
  -0.991205;0.008743;-0.132050;,
  -0.991349;0.005114;-0.131155;,
  -0.991510;0.003852;-0.129975;,
  -0.991489;0.003620;-0.130138;,
  -0.991519;0.003691;-0.129913;,
  -0.991583;0.002725;-0.129445;,
  -0.991388;0.003520;-0.130910;,
  -0.991607;0.001763;-0.129276;,
  -0.991977;-0.002704;-0.126386;,
  -0.991931;-0.001970;-0.126767;,
  -0.991735;-0.002508;-0.128276;,
  -0.992133;-0.004468;-0.125110;,
  -0.972071;0.168070;-0.163802;,
  -0.915336;0.402679;-0.003078;,
  -0.979707;0.198287;-0.029284;,
  0.993627;0.074843;-0.084285;,
  0.992522;0.049900;-0.111404;,
  0.992509;0.064102;-0.104007;,
  0.991584;0.031953;-0.125459;,
  0.991760;0.020534;-0.126451;,
  0.991780;0.019983;-0.126388;,
  0.991815;0.019550;-0.126181;,
  0.991811;0.019502;-0.126215;,
  0.991781;0.019079;-0.126517;,
  0.991685;0.018113;-0.127407;,
  0.991622;0.017271;-0.128018;,
  0.991579;0.016755;-0.128415;,
  0.991604;0.016678;-0.128231;,
  0.991600;0.016520;-0.128282;,
  0.991579;0.015271;-0.128601;,
  0.991498;0.013666;-0.129401;,
  0.991442;0.012714;-0.129925;,
  0.991388;0.012699;-0.130343;,
  0.991392;0.012921;-0.130289;,
  0.991289;0.011850;-0.131167;,
  0.991180;0.010422;-0.132108;,
  0.991188;0.010171;-0.132070;,
  0.991307;0.010349;-0.131163;,
  0.991456;0.011107;-0.129965;,
  0.991607;0.009344;-0.128950;,
  0.991522;0.010559;-0.129508;,
  0.991808;0.006873;-0.127554;,
  0.991694;0.007605;-0.128394;,
  0.991433;0.008163;-0.130358;,
  0.991205;0.008743;-0.132050;,
  0.991236;0.006523;-0.131940;,
  0.991349;0.005114;-0.131155;,
  0.991426;0.004321;-0.130596;,
  0.991510;0.003852;-0.129975;,
  0.991515;0.003752;-0.129942;,
  0.991489;0.003620;-0.130138;,
  0.991461;0.003876;-0.130346;,
  0.991519;0.003691;-0.129913;,
  0.991602;0.002906;-0.129297;,
  0.991583;0.002725;-0.129445;,
  0.991479;0.003010;-0.130233;,
  0.991388;0.003520;-0.130910;,
  0.991400;0.003397;-0.130825;,
  0.991607;0.001763;-0.129276;,
  0.991793;-0.000277;-0.127850;,
  0.991977;-0.002704;-0.126386;,
  0.991983;-0.002923;-0.126337;,
  0.991931;-0.001970;-0.126767;,
  0.991855;-0.002248;-0.127350;,
  0.991735;-0.002508;-0.128276;,
  0.991689;-0.002669;-0.128632;,
  0.992133;-0.004468;-0.125110;,
  0.980515;0.192184;0.040701;,
  0.972071;0.168070;-0.163802;,
  0.915336;0.402679;-0.003078;,
  0.979707;0.198287;-0.029284;,
  0.000000;0.998767;-0.049640;,
  0.000000;0.998500;-0.054747;,
  0.000000;0.998207;-0.059852;,
  -0.947374;0.260403;-0.186206;,
  -0.960732;-0.081488;-0.265242;,
  0.000000;-0.996014;0.089201;,
  0.000000;-0.993048;0.117712;,
  0.000000;-0.989269;0.146102;,
  0.947374;0.260403;-0.186206;,
  0.960732;-0.081488;-0.265242;,
  0.000000;-0.999076;0.042988;,
  0.000000;-0.999680;0.025317;,
  0.000000;-0.999971;0.007642;,
  -0.890427;0.397952;0.220850;,
  -0.915973;-0.025827;0.400407;,
  0.000000;0.998126;-0.061195;,
  0.000000;0.998813;-0.048700;,
  0.890427;0.397952;0.220850;,
  0.915973;-0.025827;0.400407;,
  0.000000;0.999008;-0.044533;,
  0.000000;-0.325949;-0.945387;,
  0.000000;-0.325949;-0.945387;,
  0.000000;-0.998160;0.060641;,
  0.000000;-0.998160;0.060641;,
  0.000000;-0.126027;0.992027;,
  0.000000;-0.126027;0.992027;;
  236;
  3;1,0,2;,
  3;1,2,3;,
  3;3,2,4;,
  3;3,4,5;,
  3;5,4,6;,
  3;5,6,7;,
  3;7,6,8;,
  3;7,8,9;,
  3;9,8,10;,
  3;9,10,11;,
  3;11,10,12;,
  3;11,12,13;,
  3;13,12,14;,
  3;13,14,15;,
  3;15,14,16;,
  3;15,16,17;,
  3;17,16,18;,
  3;17,18,19;,
  3;19,18,20;,
  3;19,20,21;,
  3;21,20,22;,
  3;21,22,23;,
  3;23,22,24;,
  3;23,24,25;,
  3;25,24,26;,
  3;25,26,27;,
  3;27,26,28;,
  3;27,28,29;,
  3;29,28,30;,
  3;29,30,31;,
  3;31,30,32;,
  3;31,32,33;,
  3;33,32,34;,
  3;33,34,35;,
  3;35,34,36;,
  3;35,36,37;,
  3;37,36,38;,
  3;37,38,39;,
  3;39,38,40;,
  3;39,40,41;,
  3;41,40,42;,
  3;41,42,43;,
  3;43,42,44;,
  3;43,44,45;,
  3;45,44,46;,
  3;45,46,47;,
  3;47,46,48;,
  3;47,48,49;,
  3;49,48,50;,
  3;49,50,51;,
  3;51,50,52;,
  3;103,103,103;,
  3;103,103,103;,
  3;53,54,55;,
  3;55,54,56;,
  3;55,56,57;,
  3;57,56,58;,
  3;57,58,59;,
  3;59,58,60;,
  3;59,60,61;,
  3;61,60,62;,
  3;61,62,63;,
  3;63,62,64;,
  3;65,65,65;,
  3;65,65,65;,
  3;107,107,66;,
  3;66,107,67;,
  3;66,67,68;,
  3;68,67,69;,
  3;68,69,70;,
  3;70,69,71;,
  3;70,71,72;,
  3;72,71,73;,
  3;72,73,74;,
  3;74,73,75;,
  3;104,104,104;,
  3;104,104,104;,
  3;108,102,109;,
  3;109,102,101;,
  3;109,101,110;,
  3;110,101,100;,
  3;110,100,111;,
  3;111,100,99;,
  3;111,99,112;,
  3;112,99,98;,
  3;112,98,113;,
  3;113,98,97;,
  3;113,97,114;,
  3;114,97,96;,
  3;114,96,115;,
  3;115,96,95;,
  3;115,95,116;,
  3;116,95,94;,
  3;116,94,117;,
  3;117,94,93;,
  3;117,93,118;,
  3;118,93,92;,
  3;118,92,119;,
  3;119,92,91;,
  3;119,91,120;,
  3;120,91,90;,
  3;90,89,120;,
  3;120,89,121;,
  3;89,88,121;,
  3;121,88,122;,
  3;88,87,122;,
  3;122,87,123;,
  3;87,86,123;,
  3;123,86,124;,
  3;86,85,124;,
  3;124,85,125;,
  3;85,84,125;,
  3;125,84,126;,
  3;84,83,126;,
  3;126,83,127;,
  3;83,82,127;,
  3;127,82,128;,
  3;82,81,128;,
  3;128,81,129;,
  3;81,80,129;,
  3;129,80,130;,
  3;80,79,130;,
  3;130,79,131;,
  3;79,78,131;,
  3;131,78,132;,
  3;78,77,132;,
  3;132,77,133;,
  3;77,76,133;,
  3;133,76,134;,
  3;105,105,105;,
  3;105,105,105;,
  3;135,105,136;,
  3;136,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;137,138,139;,
  3;139,138,140;,
  3;138,141,140;,
  3;140,141,142;,
  3;141,143,142;,
  3;142,143,144;,
  3;143,145,144;,
  3;144,145,146;,
  3;145,147,146;,
  3;146,147,148;,
  3;147,149,148;,
  3;148,149,150;,
  3;149,151,150;,
  3;150,151,152;,
  3;151,153,152;,
  3;152,153,154;,
  3;153,155,154;,
  3;154,155,156;,
  3;155,157,156;,
  3;156,157,158;,
  3;157,159,158;,
  3;158,159,160;,
  3;159,161,160;,
  3;160,161,162;,
  3;162,161,163;,
  3;163,161,164;,
  3;163,164,165;,
  3;165,164,166;,
  3;165,166,167;,
  3;167,166,168;,
  3;167,168,169;,
  3;169,168,170;,
  3;169,170,171;,
  3;171,170,172;,
  3;171,172,173;,
  3;173,172,174;,
  3;173,174,175;,
  3;175,174,176;,
  3;175,176,177;,
  3;177,176,178;,
  3;177,178,179;,
  3;179,178,180;,
  3;179,180,181;,
  3;181,180,182;,
  3;181,182,183;,
  3;183,182,184;,
  3;183,184,185;,
  3;185,184,186;,
  3;185,186,187;,
  3;187,186,188;,
  3;187,188,189;,
  3;189,188,190;,
  3;106,106,106;,
  3;106,106,106;,
  3;191,192,106;,
  3;106,192,106;,
  3;106,106,106;,
  3;106,106,106;,
  3;106,106,106;,
  3;106,106,106;,
  3;106,106,106;,
  3;106,106,106;,
  3;106,106,106;,
  3;106,106,106;,
  3;193,194,195;,
  3;195,194,195;,
  3;136,196,134;,
  3;134,196,197;,
  3;198,199,200;,
  3;200,199,200;,
  3;192,190,201;,
  3;201,190,202;,
  3;203,204,205;,
  3;205,204,205;,
  3;135,76,206;,
  3;206,76,207;,
  3;208,209,208;,
  3;191,210,189;,
  3;189,210,211;,
  3;194,209,212;,
  3;212,209,212;,
  3;213,75,214;,
  3;214,75,214;,
  3;204,198,215;,
  3;215,198,216;,
  3;54,52,217;,
  3;217,52,218;,
  3;209,193,212;,
  3;212,193,212;,
  3;51,53,217;,
  3;217,53,218;,
  3;199,203,215;,
  3;215,203,216;,
  3;74,213,214;,
  3;214,213,214;;
 }
 MeshTextureCoords {
  120;
  0.546626;0.456737;,
  0.560068;0.475163;,
  0.546626;0.456737;,
  0.533615;0.440180;,
  0.533615;0.440180;,
  0.520449;0.424091;,
  0.520449;0.424091;,
  0.507333;0.407852;,
  0.507333;0.407852;,
  0.494133;0.391869;,
  0.494133;0.391869;,
  0.480784;0.376332;,
  0.480784;0.376332;,
  0.467454;0.360739;,
  0.467454;0.360739;,
  0.453907;0.345802;,
  0.453907;0.345802;,
  0.440342;0.330920;,
  0.440342;0.330920;,
  0.426740;0.316148;,
  0.426740;0.316148;,
  0.412908;0.302072;,
  0.412908;0.302072;,
  0.399179;0.287685;,
  0.399179;0.287685;,
  0.385181;0.274112;,
  0.385181;0.274112;,
  0.371547;0.259437;,
  0.371547;0.259437;,
  0.357578;0.245775;,
  0.357578;0.245775;,
  0.343411;0.232710;,
  0.343411;0.232710;,
  0.329291;0.219504;,
  0.329291;0.219504;,
  0.315154;0.206349;,
  0.315154;0.206349;,
  0.300936;0.193439;,
  0.300936;0.193439;,
  0.286828;0.180197;,
  0.286828;0.180197;,
  0.272640;0.167197;,
  0.272640;0.167197;,
  0.258166;0.155062;,
  0.258166;0.155062;,
  0.243578;0.143271;,
  0.243578;0.143271;,
  0.229188;0.130882;,
  0.229188;0.130882;,
  0.214625;0.119013;,
  0.214625;0.119013;,
  0.193401;0.104288;,
  0.193401;0.104288;,
  0.188376;0.125494;,
  0.188376;0.125494;,
  0.184326;0.124355;,
  0.184326;0.124355;,
  0.188907;0.099063;,
  0.188907;0.099063;,
  0.170195;0.085650;,
  0.170195;0.085650;,
  0.155562;0.073996;,
  0.155562;0.073996;,
  0.140333;0.064139;,
  0.140333;0.064139;,
  0.124987;0.054638;,
  0.124987;0.054638;,
  0.112144;0.043512;,
  0.112144;0.043512;,
  0.118069;0.018483;,
  0.118069;0.018483;,
  0.133368;0.029314;,
  0.133368;0.029314;,
  0.148715;0.038815;,
  0.148715;0.038815;,
  0.163943;0.048672;,
  0.163943;0.048672;,
  0.178576;0.060326;,
  0.178576;0.060326;,
  0.195603;0.070745;,
  0.195603;0.070745;,
  0.202554;0.045239;,
  0.202554;0.045239;,
  0.206709;0.049443;,
  0.206709;0.049443;,
  0.568825;0.445532;,
  0.555922;0.428649;,
  0.542881;0.412182;,
  0.529768;0.395933;,
  0.516593;0.379874;,
  0.503272;0.364252;,
  0.489965;0.348592;,
  0.476586;0.333147;,
  0.462942;0.318501;,
  0.449385;0.303595;,
  0.435610;0.289346;,
  0.421963;0.274711;,
  0.408287;0.260165;,
  0.394532;0.245857;,
  0.380468;0.232481;,
  0.366555;0.218651;,
  0.352517;0.205195;,
  0.338406;0.191962;,
  0.324221;0.178953;,
  0.310148;0.165607;,
  0.295867;0.152888;,
  0.281699;0.139827;,
  0.267568;0.126652;,
  0.252995;0.114818;,
  0.238478;0.102810;,
  0.223840;0.091171;,
  0.201380;0.072016;,
  0.201380;0.072016;,
  0.195603;0.070745;,
  0.193401;0.104288;,
  0.188907;0.099063;,
  0.201380;0.072016;,
  0.193401;0.104288;,
  0.195603;0.070745;,
  0.188907;0.099063;;
 }
}
