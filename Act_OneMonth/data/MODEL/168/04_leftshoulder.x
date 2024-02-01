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
 50;
 2.36728;0.01608;-1.05614;,
 -0.75693;-0.64236;-1.20610;,
 1.04930;1.04376;-1.05614;,
 -0.06921;0.56658;-1.09576;,
 -0.78904;-0.90093;0.00000;,
 -0.77299;-0.77164;0.60305;,
 -0.33037;1.06821;0.00000;,
 -0.34642;0.93893;0.60305;,
 -0.06921;0.56658;1.09576;,
 -0.48913;-0.15555;1.09576;,
 1.04930;1.04376;1.05614;,
 2.36728;0.01608;1.05614;,
 6.05128;1.69718;0.58125;,
 6.25998;-0.32762;0.58125;,
 6.04230;1.78424;0.00000;,
 6.27461;-0.46959;-0.00000;,
 0.83257;1.68518;0.00000;,
 -0.33037;1.06821;0.00000;,
 0.84300;1.58392;0.58125;,
 -0.34642;0.93893;0.60305;,
 2.38473;-0.43032;0.58125;,
 -0.77299;-0.77164;0.60305;,
 2.39936;-0.57229;-0.00000;,
 -0.78904;-0.90093;0.00000;,
 6.62147;-0.13188;-1.77875;,
 6.50973;0.95222;-1.77875;,
 6.04230;1.78424;0.00000;,
 6.05128;1.69718;0.58125;,
 6.50973;0.95222;1.77875;,
 6.62147;-0.13188;1.77875;,
 6.25998;-0.32762;0.58125;,
 6.27461;-0.46959;-0.00000;,
 -0.77299;-0.77164;-0.60305;,
 -0.34642;0.93893;-0.60305;,
 -0.34642;0.93893;-0.60305;,
 0.84300;1.58392;-0.58125;,
 6.05128;1.69718;-0.58125;,
 6.25998;-0.32762;-0.58125;,
 6.05128;1.69718;-0.58125;,
 6.25998;-0.32762;-0.58125;,
 2.38473;-0.43032;-0.58125;,
 -0.77299;-0.77164;-0.60305;,
 6.50973;0.95222;-1.77875;,
 6.62147;-0.13188;-1.77875;,
 1.04930;1.04376;1.05614;,
 6.50973;0.95222;1.77875;,
 -0.06921;0.56658;1.09576;,
 2.36728;0.01608;1.05614;,
 -0.48913;-0.15555;1.09576;,
 6.62147;-0.13188;1.77875;;
 
 56;
 3;0,1,2;,
 3;1,3,2;,
 3;4,5,6;,
 3;5,7,6;,
 3;8,9,10;,
 3;9,11,10;,
 3;12,13,14;,
 3;13,15,14;,
 3;16,17,18;,
 3;17,19,18;,
 3;20,21,22;,
 3;21,23,22;,
 3;24,0,25;,
 3;0,2,25;,
 3;16,18,26;,
 3;18,27,26;,
 3;10,11,28;,
 3;11,29,28;,
 3;20,22,30;,
 3;22,31,30;,
 3;32,4,33;,
 3;4,6,33;,
 3;34,17,35;,
 3;17,16,35;,
 3;36,35,26;,
 3;35,16,26;,
 3;15,37,14;,
 3;37,38,14;,
 3;31,22,39;,
 3;22,40,39;,
 3;23,41,22;,
 3;41,40,22;,
 3;1,32,3;,
 3;32,33,3;,
 3;2,3,35;,
 3;3,34,35;,
 3;25,2,36;,
 3;2,35,36;,
 3;38,37,42;,
 3;37,43,42;,
 3;40,0,39;,
 3;0,24,39;,
 3;41,1,40;,
 3;1,0,40;,
 3;29,13,28;,
 3;13,12,28;,
 3;18,44,27;,
 3;44,45,27;,
 3;19,46,18;,
 3;46,44,18;,
 3;5,9,7;,
 3;9,8,7;,
 3;47,48,20;,
 3;48,21,20;,
 3;49,47,30;,
 3;47,20,30;;
 
 MeshMaterialList {
  1;
  56;
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
    "data\\TEXTURE\\UV_168.png";
   }
  }
 }
 MeshNormals {
  50;
  -0.168020;-0.017318;-0.985631;,
  -0.150515;-0.093645;-0.984163;,
  0.078791;-0.208473;-0.974849;,
  -0.369698;0.418090;-0.829774;,
  -0.109638;-0.235794;0.965599;,
  -0.317989;0.432867;0.843510;,
  -0.168020;-0.017318;0.985631;,
  -0.150515;-0.093645;0.984163;,
  -0.013110;-0.343183;-0.939177;,
  -0.072687;0.377406;-0.923191;,
  -0.068444;0.352887;0.933159;,
  -0.046368;-0.350818;0.935295;,
  -0.972720;0.231893;-0.006460;,
  -0.753035;0.657974;-0.003055;,
  -0.250919;0.968008;0.000000;,
  0.994730;0.102530;0.000000;,
  0.994730;0.102530;0.000000;,
  0.066282;-0.997801;0.000000;,
  -0.929316;0.327517;-0.170599;,
  -0.804104;0.496018;-0.327694;,
  -0.238810;0.865085;-0.441133;,
  -0.032570;0.863832;-0.502726;,
  0.983032;0.101323;0.152909;,
  0.091233;-0.901293;-0.423494;,
  0.983032;0.101323;-0.152909;,
  0.983032;0.101323;-0.152911;,
  -0.238810;0.865085;0.441133;,
  -0.750413;0.528261;0.397266;,
  -0.968063;0.236033;0.084515;,
  0.057978;-0.838405;0.541956;,
  0.098167;-0.901666;0.421144;,
  0.102530;-0.994730;-0.000000;,
  -0.020379;0.999792;0.000000;,
  -0.032570;0.863832;0.502726;,
  0.001556;-0.938724;0.344667;,
  0.026492;-0.999649;-0.000000;,
  0.983032;0.101323;0.152911;,
  0.001556;-0.938724;-0.344667;,
  0.104311;-0.970637;-0.216754;,
  -0.869497;0.487204;0.081289;,
  -0.057845;0.837600;-0.543213;,
  0.948217;0.097734;0.302214;,
  0.948217;0.097734;0.302214;,
  -0.064708;-0.981541;-0.179973;,
  0.106570;-0.972794;-0.205706;,
  0.948217;0.097734;-0.302214;,
  0.948217;0.097734;-0.302214;,
  -0.057845;0.837600;0.543213;,
  -0.939872;0.234379;0.248409;,
  -0.064708;-0.981541;0.179973;;
  56;
  3;8,2,9;,
  3;2,3,9;,
  3;12,28,13;,
  3;28,27,13;,
  3;5,4,10;,
  3;4,11,10;,
  3;25,24,15;,
  3;24,16,15;,
  3;14,13,26;,
  3;13,27,26;,
  3;29,30,17;,
  3;30,31,17;,
  3;0,8,1;,
  3;8,9,1;,
  3;14,26,32;,
  3;26,33,32;,
  3;10,11,7;,
  3;11,6,7;,
  3;29,17,34;,
  3;17,35,34;,
  3;18,12,19;,
  3;12,13,19;,
  3;19,13,20;,
  3;13,14,20;,
  3;21,20,32;,
  3;20,14,32;,
  3;16,22,15;,
  3;22,36,15;,
  3;35,17,37;,
  3;17,23,37;,
  3;31,38,17;,
  3;38,23,17;,
  3;39,18,39;,
  3;18,19,3;,
  3;9,3,20;,
  3;3,19,20;,
  3;40,9,21;,
  3;9,20,21;,
  3;36,22,41;,
  3;22,42,41;,
  3;23,8,37;,
  3;43,43,37;,
  3;38,44,23;,
  3;2,8,23;,
  3;45,24,46;,
  3;24,25,46;,
  3;26,10,33;,
  3;10,47,33;,
  3;27,5,26;,
  3;5,10,26;,
  3;28,48,27;,
  3;4,5,27;,
  3;11,4,29;,
  3;4,30,29;,
  3;49,49,34;,
  3;11,29,34;;
 }
 MeshTextureCoords {
  50;
  0.740121;0.305529;,
  0.740121;0.284232;,
  0.782714;0.305529;,
  0.782714;0.284232;,
  0.740121;0.262936;,
  0.740121;0.252288;,
  0.782714;0.262936;,
  0.782714;0.252288;,
  0.782714;0.241640;,
  0.740121;0.241640;,
  0.782714;0.220344;,
  0.740121;0.220344;,
  0.782714;0.188399;,
  0.740121;0.188399;,
  0.782714;0.177751;,
  0.740121;0.177751;,
  0.804010;0.305529;,
  0.804010;0.284232;,
  0.814658;0.305529;,
  0.814658;0.284232;,
  0.708177;0.305529;,
  0.708177;0.284232;,
  0.718825;0.305529;,
  0.718825;0.284232;,
  0.740121;0.326825;,
  0.782714;0.326825;,
  0.804010;0.326825;,
  0.814658;0.326825;,
  0.782714;0.199047;,
  0.740121;0.199047;,
  0.708177;0.326825;,
  0.718825;0.326825;,
  0.740121;0.273584;,
  0.782714;0.273584;,
  0.793362;0.284232;,
  0.793362;0.305529;,
  0.793362;0.326825;,
  0.740121;0.167103;,
  0.782714;0.167103;,
  0.729473;0.326825;,
  0.729473;0.305529;,
  0.729473;0.284232;,
  0.782714;0.156455;,
  0.740121;0.156455;,
  0.825306;0.305529;,
  0.825306;0.326825;,
  0.825306;0.284232;,
  0.697529;0.305529;,
  0.697529;0.284232;,
  0.697529;0.326825;;
 }
}
