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
 298;
 0.00000;57.33992;0.00000;,
 3.00365;56.49498;-3.00365;,
 0.00000;56.49498;-4.24778;,
 0.00000;57.33992;0.00000;,
 4.24778;56.49498;0.00000;,
 0.00000;57.33992;0.00000;,
 3.00365;56.49498;3.00365;,
 0.00000;57.33992;0.00000;,
 0.00000;56.49498;4.24778;,
 0.00000;57.33992;0.00000;,
 -3.00365;56.49498;3.00365;,
 0.00000;57.33992;0.00000;,
 -4.24778;56.49498;0.00000;,
 0.00000;57.33992;0.00000;,
 -3.00365;56.49498;-3.00365;,
 0.00000;57.33992;0.00000;,
 0.00000;56.49498;-4.24778;,
 5.55000;54.08880;-5.55000;,
 0.00000;54.08880;-7.84888;,
 7.84888;54.08880;0.00000;,
 5.55000;54.08880;5.55000;,
 0.00000;54.08880;7.84888;,
 -5.55000;54.08880;5.55000;,
 -7.84888;54.08880;0.00000;,
 -5.55000;54.08880;-5.55000;,
 0.00000;54.08880;-7.84888;,
 7.25142;50.48770;-7.25142;,
 0.00000;50.48770;-10.25508;,
 10.25508;50.48770;0.00000;,
 7.25142;50.48770;7.25142;,
 0.00000;50.48770;10.25508;,
 -7.25142;50.48770;7.25142;,
 -10.25508;50.48770;0.00000;,
 -7.25142;50.48770;-7.25142;,
 0.00000;50.48770;-10.25508;,
 7.84888;46.23993;-7.84888;,
 0.00000;46.23993;-11.10000;,
 11.10000;46.23993;0.00000;,
 7.84888;46.23993;7.84888;,
 0.00000;46.23993;11.10000;,
 -7.84888;46.23993;7.84888;,
 -11.10000;46.23993;0.00000;,
 -7.84888;46.23993;-7.84888;,
 0.00000;46.23993;-11.10000;,
 7.25142;41.99213;-7.25142;,
 0.00000;41.99213;-10.25508;,
 10.25508;41.99213;0.00000;,
 7.25142;41.99213;7.25142;,
 0.00000;41.99213;10.25508;,
 -7.25142;41.99213;7.25142;,
 -10.25508;41.99213;0.00000;,
 -7.25142;41.99213;-7.25142;,
 0.00000;41.99213;-10.25508;,
 5.55000;38.39103;-5.55000;,
 0.00000;38.39103;-7.84888;,
 7.84888;38.39103;0.00000;,
 5.55000;38.39103;5.55000;,
 0.00000;38.39103;7.84888;,
 -5.55000;38.39103;5.55000;,
 -7.84888;38.39103;0.00000;,
 -5.55000;38.39103;-5.55000;,
 0.00000;38.39103;-7.84888;,
 3.00365;35.98485;-3.00365;,
 0.00000;35.98485;-4.24778;,
 4.24778;35.98485;0.00000;,
 3.00365;35.98485;3.00365;,
 0.00000;35.98485;4.24778;,
 -3.00365;35.98485;3.00365;,
 -4.24778;35.98485;0.00000;,
 -3.00365;35.98485;-3.00365;,
 0.00000;35.98485;-4.24778;,
 0.00000;35.13992;0.00000;,
 0.00000;35.13992;0.00000;,
 0.00000;35.13992;0.00000;,
 0.00000;35.13992;0.00000;,
 0.00000;35.13992;0.00000;,
 0.00000;35.13992;0.00000;,
 0.00000;35.13992;0.00000;,
 0.00000;35.13992;0.00000;,
 0.00000;103.51270;0.00000;,
 8.45235;100.24093;-8.45235;,
 0.00000;100.24093;-11.95343;,
 0.00000;103.51270;0.00000;,
 11.95343;100.24093;0.00000;,
 0.00000;103.51270;0.00000;,
 8.45235;100.24093;8.45235;,
 0.00000;103.51270;0.00000;,
 0.00000;100.24093;11.95343;,
 0.00000;103.51270;0.00000;,
 -8.45235;100.24093;8.45232;,
 0.00000;103.51270;0.00000;,
 -11.95343;100.24093;0.00000;,
 0.00000;103.51270;0.00000;,
 -8.45235;100.24093;-8.45232;,
 0.00000;103.51270;0.00000;,
 0.00000;100.24093;-11.95343;,
 15.61788;90.92372;-15.61788;,
 0.00000;90.92372;-22.08702;,
 22.08702;90.92372;0.00000;,
 15.61788;90.92372;15.61788;,
 0.00000;90.92372;22.08702;,
 -15.61790;90.92372;15.61788;,
 -22.08702;90.92372;0.00000;,
 -15.61790;90.92372;-15.61788;,
 0.00000;90.92372;-22.08702;,
 20.40575;76.97952;-20.40575;,
 0.00000;76.97952;-28.85810;,
 28.85810;76.97952;0.00000;,
 20.40575;76.97952;20.40575;,
 0.00000;76.97952;28.85810;,
 -20.40575;76.97952;20.40575;,
 -28.85810;76.97952;0.00000;,
 -20.40575;76.97952;-20.40575;,
 0.00000;76.97952;-28.85810;,
 22.08702;60.53128;-22.08702;,
 0.00000;60.53128;-31.23577;,
 31.23577;60.53128;0.00000;,
 22.08702;60.53128;22.08702;,
 0.00000;60.53128;31.23577;,
 -22.08702;60.53128;22.08702;,
 -31.23577;60.53128;0.00000;,
 -22.08702;60.53128;-22.08702;,
 0.00000;60.53128;-31.23577;,
 0.00000;33.85757;-15.38408;,
 10.87817;33.85757;-10.87817;,
 10.05013;21.66327;-10.05013;,
 0.00000;21.66327;-14.21303;,
 15.38408;33.85757;0.00000;,
 14.21303;21.66327;0.00000;,
 10.87817;33.85757;10.87817;,
 10.05013;21.66327;10.05013;,
 0.00000;33.85757;15.38408;,
 0.00000;21.66327;14.21303;,
 -10.87820;33.85757;10.87817;,
 -10.05013;21.66327;10.05013;,
 -15.38408;33.85757;0.00000;,
 -14.21303;21.66327;0.00000;,
 -10.87820;33.85757;-10.87817;,
 -10.05013;21.66327;-10.05013;,
 0.00000;33.85757;-15.38408;,
 0.00000;21.66327;-14.21303;,
 7.69205;11.32545;-7.69205;,
 0.00000;11.32545;-10.87817;,
 10.87817;11.32545;0.00000;,
 7.69205;11.32545;7.69205;,
 0.00000;11.32545;10.87817;,
 -7.69205;11.32545;7.69203;,
 -10.87817;11.32545;0.00000;,
 -7.69205;11.32545;-7.69203;,
 0.00000;11.32545;-10.87817;,
 4.16290;4.41795;-4.16290;,
 0.00000;4.41795;-5.88723;,
 5.88723;4.41795;0.00000;,
 4.16290;4.41795;4.16290;,
 0.00000;4.41795;5.88723;,
 -4.16290;4.41795;4.16290;,
 -5.88723;4.41795;0.00000;,
 -4.16290;4.41795;-4.16290;,
 0.00000;4.41795;-5.88723;,
 0.00000;1.99238;0.00000;,
 0.00000;1.99238;0.00000;,
 0.00000;1.99238;0.00000;,
 0.00000;1.99238;0.00000;,
 0.00000;1.99238;0.00000;,
 0.00000;1.99238;0.00000;,
 0.00000;1.99238;0.00000;,
 0.00000;1.99238;0.00000;,
 -62.78825;64.91935;-13.85000;,
 -26.11233;92.05820;0.00000;,
 -56.96292;57.04688;-9.79342;,
 -26.11233;92.05820;0.00000;,
 -54.54998;53.78598;0.00000;,
 -26.11233;92.05820;0.00000;,
 -56.96292;57.04688;9.79342;,
 -26.11233;92.05820;0.00000;,
 -62.78825;64.91935;13.85000;,
 -26.11233;92.05820;0.00000;,
 -68.61360;72.79188;9.79342;,
 -26.11233;92.05820;0.00000;,
 -71.02655;76.05277;0.00000;,
 -26.11233;92.05820;0.00000;,
 -68.61360;72.79188;-9.79342;,
 -26.11233;92.05820;0.00000;,
 -62.78825;64.91935;-13.85000;,
 -62.78825;64.91935;0.00000;,
 -62.78825;64.91935;-13.85000;,
 -56.96292;57.04688;-9.79342;,
 -54.54998;53.78598;0.00000;,
 -56.96292;57.04688;9.79342;,
 -62.78825;64.91935;13.85000;,
 -68.61360;72.79188;9.79342;,
 -71.02655;76.05277;0.00000;,
 -68.61360;72.79188;-9.79342;,
 61.48115;63.97825;-13.85000;,
 26.27578;92.99928;0.00000;,
 67.71055;71.53510;-9.79342;,
 26.27578;92.99928;0.00000;,
 70.29085;74.66525;0.00000;,
 26.27578;92.99928;0.00000;,
 67.71055;71.53510;9.79342;,
 26.27578;92.99928;0.00000;,
 61.48115;63.97825;13.85000;,
 26.27578;92.99928;0.00000;,
 55.25177;56.42138;9.79342;,
 26.27578;92.99928;0.00000;,
 52.67145;53.29125;0.00000;,
 26.27578;92.99928;0.00000;,
 55.25177;56.42138;-9.79342;,
 26.27578;92.99928;0.00000;,
 61.48115;63.97825;-13.85000;,
 61.48115;63.97825;0.00000;,
 61.48115;63.97825;-13.85000;,
 67.71055;71.53510;-9.79342;,
 70.29085;74.66525;0.00000;,
 67.71055;71.53510;9.79342;,
 61.48115;63.97825;13.85000;,
 55.25177;56.42138;9.79342;,
 52.67145;53.29125;0.00000;,
 55.25177;56.42138;-9.79342;,
 0.07948;128.86273;0.00000;,
 3.09665;128.01401;-3.01717;,
 0.07948;128.01401;-4.26692;,
 0.07948;128.86273;0.00000;,
 4.34640;128.01401;0.00000;,
 0.07948;128.86273;0.00000;,
 3.09665;128.01401;3.01717;,
 0.07948;128.86273;0.00000;,
 0.07948;128.01401;4.26692;,
 0.07948;128.86273;0.00000;,
 -2.93770;128.01401;3.01717;,
 0.07948;128.86273;0.00000;,
 -4.18745;128.01401;0.00000;,
 0.07948;128.86273;0.00000;,
 -2.93770;128.01401;-3.01717;,
 0.07948;128.86273;0.00000;,
 0.07948;128.01401;-4.26692;,
 5.65448;125.59698;-5.57500;,
 0.07948;125.59698;-7.88425;,
 7.96370;125.59698;0.00000;,
 5.65448;125.59698;5.57500;,
 0.07948;125.59698;7.88425;,
 -5.49552;125.59698;5.57500;,
 -7.80478;125.59698;0.00000;,
 -5.49552;125.59698;-5.57500;,
 0.07948;125.59698;-7.88425;,
 7.36355;121.97965;-7.28410;,
 0.07948;121.97965;-10.30125;,
 10.38072;121.97965;0.00000;,
 7.36355;121.97965;7.28410;,
 0.07948;121.97965;10.30125;,
 -7.20463;121.97965;7.28407;,
 -10.22178;121.97965;0.00000;,
 -7.20463;121.97965;-7.28407;,
 0.07948;121.97965;-10.30125;,
 7.96370;117.71275;-7.88425;,
 0.07948;117.71275;-11.15000;,
 11.22948;117.71275;0.00000;,
 7.96370;117.71275;7.88425;,
 0.07948;117.71275;11.15000;,
 -7.80478;117.71275;7.88425;,
 -11.07053;117.71275;0.00000;,
 -7.80478;117.71275;-7.88425;,
 0.07948;117.71275;-11.15000;,
 7.36355;113.44582;-7.28410;,
 0.07948;113.44582;-10.30125;,
 10.38072;113.44582;0.00000;,
 7.36355;113.44582;7.28410;,
 0.07948;113.44582;10.30125;,
 -7.20463;113.44582;7.28407;,
 -10.22178;113.44582;0.00000;,
 -7.20463;113.44582;-7.28407;,
 0.07948;113.44582;-10.30125;,
 5.65448;109.82850;-5.57500;,
 0.07948;109.82850;-7.88425;,
 7.96370;109.82850;0.00000;,
 5.65448;109.82850;5.57500;,
 0.07948;109.82850;7.88425;,
 -5.49552;109.82850;5.57500;,
 -7.80478;109.82850;0.00000;,
 -5.49552;109.82850;-5.57500;,
 0.07948;109.82850;-7.88425;,
 3.09665;107.41148;-3.01717;,
 0.07948;107.41148;-4.26692;,
 4.34640;107.41148;0.00000;,
 3.09665;107.41148;3.01717;,
 0.07948;107.41148;4.26692;,
 -2.93770;107.41148;3.01717;,
 -4.18745;107.41148;0.00000;,
 -2.93770;107.41148;-3.01717;,
 0.07948;107.41148;-4.26692;,
 0.07948;106.56272;0.00000;,
 0.07948;106.56272;0.00000;,
 0.07948;106.56272;0.00000;,
 0.07948;106.56272;0.00000;,
 0.07948;106.56272;0.00000;,
 0.07948;106.56272;0.00000;,
 0.07948;106.56272;0.00000;,
 0.07948;106.56272;0.00000;;
 
 224;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 3;79,80,81;,
 3;82,83,80;,
 3;84,85,83;,
 3;86,87,85;,
 3;88,89,87;,
 3;90,91,89;,
 3;92,93,91;,
 3;94,95,93;,
 4;81,80,96,97;,
 4;80,83,98,96;,
 4;83,85,99,98;,
 4;85,87,100,99;,
 4;87,89,101,100;,
 4;89,91,102,101;,
 4;91,93,103,102;,
 4;93,95,104,103;,
 4;97,96,105,106;,
 4;96,98,107,105;,
 4;98,99,108,107;,
 4;99,100,109,108;,
 4;100,101,110,109;,
 4;101,102,111,110;,
 4;102,103,112,111;,
 4;103,104,113,112;,
 4;106,105,114,115;,
 4;105,107,116,114;,
 4;107,108,117,116;,
 4;108,109,118,117;,
 4;109,110,119,118;,
 4;110,111,120,119;,
 4;111,112,121,120;,
 4;112,113,122,121;,
 4;123,124,125,126;,
 4;124,127,128,125;,
 4;127,129,130,128;,
 4;129,131,132,130;,
 4;131,133,134,132;,
 4;133,135,136,134;,
 4;135,137,138,136;,
 4;137,139,140,138;,
 4;126,125,141,142;,
 4;125,128,143,141;,
 4;128,130,144,143;,
 4;130,132,145,144;,
 4;132,134,146,145;,
 4;134,136,147,146;,
 4;136,138,148,147;,
 4;138,140,149,148;,
 4;142,141,150,151;,
 4;141,143,152,150;,
 4;143,144,153,152;,
 4;144,145,154,153;,
 4;145,146,155,154;,
 4;146,147,156,155;,
 4;147,148,157,156;,
 4;148,149,158,157;,
 3;151,150,159;,
 3;150,152,160;,
 3;152,153,161;,
 3;153,154,162;,
 3;154,155,163;,
 3;155,156,164;,
 3;156,157,165;,
 3;157,158,166;,
 3;167,168,169;,
 3;169,170,171;,
 3;171,172,173;,
 3;173,174,175;,
 3;175,176,177;,
 3;177,178,179;,
 3;179,180,181;,
 3;181,182,183;,
 3;184,185,186;,
 3;184,186,187;,
 3;184,187,188;,
 3;184,188,189;,
 3;184,189,190;,
 3;184,190,191;,
 3;184,191,192;,
 3;184,192,185;,
 3;193,194,195;,
 3;195,196,197;,
 3;197,198,199;,
 3;199,200,201;,
 3;201,202,203;,
 3;203,204,205;,
 3;205,206,207;,
 3;207,208,209;,
 3;210,211,212;,
 3;210,212,213;,
 3;210,213,214;,
 3;210,214,215;,
 3;210,215,216;,
 3;210,216,217;,
 3;210,217,218;,
 3;210,218,211;,
 3;219,220,221;,
 3;222,223,220;,
 3;224,225,223;,
 3;226,227,225;,
 3;228,229,227;,
 3;230,231,229;,
 3;232,233,231;,
 3;234,235,233;,
 4;221,220,236,237;,
 4;220,223,238,236;,
 4;223,225,239,238;,
 4;225,227,240,239;,
 4;227,229,241,240;,
 4;229,231,242,241;,
 4;231,233,243,242;,
 4;233,235,244,243;,
 4;237,236,245,246;,
 4;236,238,247,245;,
 4;238,239,248,247;,
 4;239,240,249,248;,
 4;240,241,250,249;,
 4;241,242,251,250;,
 4;242,243,252,251;,
 4;243,244,253,252;,
 4;246,245,254,255;,
 4;245,247,256,254;,
 4;247,248,257,256;,
 4;248,249,258,257;,
 4;249,250,259,258;,
 4;250,251,260,259;,
 4;251,252,261,260;,
 4;252,253,262,261;,
 4;255,254,263,264;,
 4;254,256,265,263;,
 4;256,257,266,265;,
 4;257,258,267,266;,
 4;258,259,268,267;,
 4;259,260,269,268;,
 4;260,261,270,269;,
 4;261,262,271,270;,
 4;264,263,272,273;,
 4;263,265,274,272;,
 4;265,266,275,274;,
 4;266,267,276,275;,
 4;267,268,277,276;,
 4;268,269,278,277;,
 4;269,270,279,278;,
 4;270,271,280,279;,
 4;273,272,281,282;,
 4;272,274,283,281;,
 4;274,275,284,283;,
 4;275,276,285,284;,
 4;276,277,286,285;,
 4;277,278,287,286;,
 4;278,279,288,287;,
 4;279,280,289,288;,
 3;282,281,290;,
 3;281,283,291;,
 3;283,284,292;,
 3;284,285,293;,
 3;285,286,294;,
 3;286,287,295;,
 3;287,288,296;,
 3;288,289,297;;
 
 MeshMaterialList {
  2;
  224;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  1,
  1;;
  Material {
   0.762353;0.219608;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  214;
  -0.000000;1.000000;0.000000;,
  0.000000;0.924735;-0.380613;,
  0.269133;0.924735;-0.269133;,
  0.380613;0.924735;0.000000;,
  0.269133;0.924735;0.269133;,
  0.000000;0.924735;0.380613;,
  -0.269133;0.924735;0.269133;,
  -0.380613;0.924735;0.000000;,
  -0.269133;0.924735;-0.269133;,
  0.000000;0.709231;-0.704976;,
  0.498493;0.709231;-0.498493;,
  0.704976;0.709231;0.000000;,
  0.498493;0.709231;0.498493;,
  0.000000;0.709231;0.704976;,
  -0.498493;0.709231;0.498493;,
  -0.704976;0.709231;0.000000;,
  -0.498493;0.709231;-0.498493;,
  0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  0.000000;0.000001;-1.000000;,
  0.707107;0.000001;-0.707107;,
  1.000000;0.000001;0.000000;,
  0.707107;0.000001;0.707107;,
  0.000000;0.000001;1.000000;,
  -0.707107;0.000001;0.707107;,
  -1.000000;0.000001;0.000000;,
  -0.707107;0.000001;-0.707107;,
  0.000000;-0.384550;-0.923104;,
  0.652733;-0.384550;-0.652733;,
  0.923104;-0.384550;-0.000000;,
  0.652733;-0.384550;0.652733;,
  0.000000;-0.384550;0.923104;,
  -0.652733;-0.384550;0.652733;,
  -0.923104;-0.384550;0.000000;,
  -0.652733;-0.384550;-0.652733;,
  0.000000;-0.709231;-0.704976;,
  0.498493;-0.709231;-0.498493;,
  0.704976;-0.709231;-0.000000;,
  0.498493;-0.709231;0.498493;,
  0.000000;-0.709231;0.704976;,
  -0.498493;-0.709231;0.498493;,
  -0.704976;-0.709231;0.000000;,
  -0.498493;-0.709231;-0.498493;,
  0.000000;-0.924735;-0.380610;,
  0.269131;-0.924736;-0.269131;,
  0.380610;-0.924735;-0.000000;,
  0.269131;-0.924736;0.269131;,
  0.000000;-0.924735;0.380610;,
  -0.269131;-0.924736;0.269131;,
  -0.380610;-0.924735;0.000000;,
  -0.269131;-0.924736;-0.269131;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.876892;-0.480687;,
  0.339898;0.876892;-0.339898;,
  0.480688;0.876892;0.000000;,
  0.339898;0.876892;0.339898;,
  -0.000000;0.876892;0.480687;,
  -0.339898;0.876892;0.339897;,
  -0.480687;0.876892;0.000000;,
  -0.339898;0.876892;-0.339897;,
  -0.000000;0.599020;-0.800734;,
  0.566205;0.599020;-0.566205;,
  0.800734;0.599020;0.000000;,
  0.566205;0.599020;0.566205;,
  -0.000000;0.599020;0.800734;,
  -0.566205;0.599020;0.566204;,
  -0.800734;0.599020;0.000000;,
  -0.566205;0.599020;-0.566204;,
  0.000000;0.294363;-0.955694;,
  0.675777;0.294363;-0.675777;,
  0.955694;0.294363;0.000000;,
  0.675777;0.294363;0.675777;,
  0.000000;0.294363;0.955694;,
  -0.675777;0.294363;0.675777;,
  -0.955694;0.294363;0.000000;,
  -0.675777;0.294363;-0.675777;,
  0.000000;0.143068;-0.989713;,
  0.699833;0.143068;-0.699833;,
  0.989713;0.143068;0.000000;,
  0.699833;0.143068;0.699833;,
  0.000000;0.143068;0.989713;,
  -0.699833;0.143068;0.699833;,
  -0.989713;0.143068;0.000000;,
  -0.699833;0.143068;-0.699833;,
  0.000000;-0.095593;-0.995421;,
  0.703869;-0.095592;-0.703869;,
  0.995421;-0.095592;-0.000000;,
  0.703869;-0.095592;0.703869;,
  0.000000;-0.095593;0.995421;,
  -0.703869;-0.095593;0.703868;,
  -0.995420;-0.095593;0.000000;,
  -0.703869;-0.095593;-0.703868;,
  -0.000000;-0.202817;-0.979217;,
  0.692411;-0.202817;-0.692411;,
  0.979217;-0.202817;-0.000000;,
  0.692411;-0.202817;0.692411;,
  -0.000000;-0.202817;0.979217;,
  -0.692411;-0.202818;0.692410;,
  -0.979217;-0.202817;0.000000;,
  -0.692411;-0.202818;-0.692410;,
  -0.000001;-0.453206;-0.891406;,
  0.630319;-0.453206;-0.630319;,
  0.891406;-0.453206;-0.000000;,
  0.630319;-0.453206;0.630319;,
  -0.000001;-0.453206;0.891406;,
  -0.630319;-0.453206;0.630319;,
  -0.891406;-0.453206;0.000000;,
  -0.630319;-0.453206;-0.630319;,
  -0.000000;-0.788696;-0.614784;,
  0.434717;-0.788696;-0.434717;,
  0.614784;-0.788696;-0.000000;,
  0.434717;-0.788696;0.434717;,
  -0.000000;-0.788696;0.614784;,
  -0.434718;-0.788696;0.434717;,
  -0.614784;-0.788696;0.000000;,
  -0.434718;-0.788696;-0.434717;,
  0.000000;-1.000000;-0.000000;,
  0.233499;0.172779;-0.956883;,
  0.635967;-0.371125;-0.676618;,
  0.802675;-0.596417;-0.000000;,
  0.635967;-0.371125;0.676618;,
  0.233499;0.172779;0.956883;,
  -0.168970;0.716684;0.676619;,
  -0.335678;0.941977;0.000000;,
  -0.168970;0.716684;-0.676619;,
  -0.803857;-0.594823;0.000000;,
  -0.803857;-0.594822;0.000000;,
  -0.803857;-0.594823;0.000000;,
  -0.803857;-0.594823;0.000000;,
  -0.803857;-0.594823;-0.000000;,
  -0.803857;-0.594822;0.000001;,
  -0.803857;-0.594823;0.000000;,
  -0.803857;-0.594822;-0.000001;,
  -0.224136;0.184764;-0.956883;,
  0.206246;0.706859;-0.676619;,
  0.384516;0.923119;0.000000;,
  0.206246;0.706859;0.676619;,
  -0.224136;0.184764;0.956883;,
  -0.654518;-0.337332;0.676619;,
  -0.832788;-0.553591;0.000000;,
  -0.654518;-0.337332;-0.676619;,
  0.771625;-0.636078;-0.000000;,
  0.771625;-0.636078;-0.000000;,
  0.771624;-0.636079;-0.000000;,
  0.771624;-0.636079;-0.000000;,
  0.771624;-0.636079;0.000000;,
  0.771625;-0.636078;-0.000002;,
  0.771624;-0.636079;-0.000000;,
  0.771625;-0.636078;0.000002;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.924736;-0.380610;,
  0.269132;0.924736;-0.269132;,
  0.380611;0.924735;0.000000;,
  0.269132;0.924736;0.269132;,
  -0.000000;0.924736;0.380610;,
  -0.269132;0.924736;0.269132;,
  -0.380610;0.924736;0.000000;,
  -0.269132;0.924736;-0.269132;,
  -0.000000;0.709228;-0.704979;,
  0.498495;0.709229;-0.498495;,
  0.704979;0.709228;0.000000;,
  0.498495;0.709229;0.498495;,
  -0.000000;0.709228;0.704979;,
  -0.498495;0.709228;0.498495;,
  -0.704979;0.709229;0.000000;,
  -0.498495;0.709228;-0.498495;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652732;,
  -0.000000;0.000001;-1.000000;,
  0.707106;0.000001;-0.707107;,
  1.000000;0.000001;0.000000;,
  0.707106;0.000001;0.707107;,
  -0.000000;0.000001;1.000000;,
  -0.707107;0.000001;0.707106;,
  -1.000000;0.000001;0.000000;,
  -0.707107;0.000001;-0.707106;,
  -0.000000;-0.384550;-0.923104;,
  0.652733;-0.384550;-0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384550;0.652733;,
  -0.000000;-0.384550;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384550;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  -0.000000;-0.709229;-0.704978;,
  0.498495;-0.709229;-0.498494;,
  0.704978;-0.709229;-0.000000;,
  0.498495;-0.709229;0.498494;,
  -0.000000;-0.709229;0.704978;,
  -0.498495;-0.709229;0.498495;,
  -0.704978;-0.709229;0.000000;,
  -0.498495;-0.709229;-0.498495;,
  0.000000;-0.924735;-0.380613;,
  0.269134;-0.924735;-0.269134;,
  0.380614;-0.924734;-0.000000;,
  0.269134;-0.924735;0.269134;,
  0.000000;-0.924735;0.380613;,
  -0.269134;-0.924735;0.269134;,
  -0.380613;-0.924735;0.000000;,
  -0.269134;-0.924735;-0.269134;,
  -0.000000;-1.000000;0.000000;;
  224;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  3;58,60,59;,
  3;58,61,60;,
  3;58,62,61;,
  3;58,63,62;,
  3;58,64,63;,
  3;58,65,64;,
  3;58,66,65;,
  3;58,59,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,66,74,73;,
  4;66,59,67,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,67,75,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,75,83,90;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,91,99,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;105,106,114,113;,
  4;106,99,107,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,113,121,120;,
  4;113,114,122,121;,
  4;114,107,115,122;,
  3;115,116,123;,
  3;116,117,123;,
  3;117,118,123;,
  3;118,119,123;,
  3;119,120,123;,
  3;120,121,123;,
  3;121,122,123;,
  3;122,115,123;,
  3;124,125,125;,
  3;125,125,126;,
  3;126,127,127;,
  3;127,127,128;,
  3;128,129,129;,
  3;129,129,130;,
  3;130,131,131;,
  3;131,131,124;,
  3;132,133,134;,
  3;132,134,135;,
  3;132,135,136;,
  3;132,136,133;,
  3;132,133,137;,
  3;132,137,138;,
  3;132,138,139;,
  3;132,139,133;,
  3;140,141,141;,
  3;141,141,142;,
  3;142,143,143;,
  3;143,143,144;,
  3;144,145,145;,
  3;145,145,146;,
  3;146,147,147;,
  3;147,147,140;,
  3;148,149,150;,
  3;148,150,151;,
  3;148,151,152;,
  3;148,152,149;,
  3;148,149,153;,
  3;148,153,154;,
  3;148,154,155;,
  3;148,155,149;,
  3;156,158,157;,
  3;156,159,158;,
  3;156,160,159;,
  3;156,161,160;,
  3;156,162,161;,
  3;156,163,162;,
  3;156,164,163;,
  3;156,157,164;,
  4;157,158,166,165;,
  4;158,159,167,166;,
  4;159,160,168,167;,
  4;160,161,169,168;,
  4;161,162,170,169;,
  4;162,163,171,170;,
  4;163,164,172,171;,
  4;164,157,165,172;,
  4;165,166,174,173;,
  4;166,167,175,174;,
  4;167,168,176,175;,
  4;168,169,177,176;,
  4;169,170,178,177;,
  4;170,171,179,178;,
  4;171,172,180,179;,
  4;172,165,173,180;,
  4;173,174,182,181;,
  4;174,175,183,182;,
  4;175,176,184,183;,
  4;176,177,185,184;,
  4;177,178,186,185;,
  4;178,179,187,186;,
  4;179,180,188,187;,
  4;180,173,181,188;,
  4;181,182,190,189;,
  4;182,183,191,190;,
  4;183,184,192,191;,
  4;184,185,193,192;,
  4;185,186,194,193;,
  4;186,187,195,194;,
  4;187,188,196,195;,
  4;188,181,189,196;,
  4;189,190,198,197;,
  4;190,191,199,198;,
  4;191,192,200,199;,
  4;192,193,201,200;,
  4;193,194,202,201;,
  4;194,195,203,202;,
  4;195,196,204,203;,
  4;196,189,197,204;,
  4;197,198,206,205;,
  4;198,199,207,206;,
  4;199,200,208,207;,
  4;200,201,209,208;,
  4;201,202,210,209;,
  4;202,203,211,210;,
  4;203,204,212,211;,
  4;204,197,205,212;,
  3;205,206,213;,
  3;206,207,213;,
  3;207,208,213;,
  3;208,209,213;,
  3;209,210,213;,
  3;210,211,213;,
  3;211,212,213;,
  3;212,205,213;;
 }
 MeshTextureCoords {
  298;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
