#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
int main(void)
{
	// Open Image File
	ifstream ifile("copy.bmp", ios::binary);
	
	// Read Header
	unsigned char header[54];
	ifile.read((char*)&header, sizeof(header));		
 	int width_ori = header[18] + header[19]*256 + header[20]*256*256 + header[21]*256*256*256;    
 	int height_ori = header[22] | header[23] << 8 | header[24] << 16 | header[25] << 24; 	
	int bits_px_ori = header[28] | header[29] << 8;

	int width = width_ori;    
 	int height = height_ori; 	
	int bits_px = bits_px_ori ;
	
	cout << "Original Image: " << width << "x" << height << "x" << bits_px << endl;	
	
	// Read RGB Data
	unsigned char original_rgb[height][width][bits_px/8];
	ifile.read((char*)&original_rgb, sizeof(original_rgb));
	ifile.close();

	

	// Image Processing
	unsigned char rgb1[height][width][bits_px/8];
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			for(int k=0; k<bits_px/8; k++)
				rgb1[i][j][k] = original_rgb[i][j][k];


	//1
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < bits_px / 8; k++)
			{
				rgb1[i][j][k] = original_rgb[height - 1 - i][width-1-j][k];
			}

		}

	}


 	width = width;
 	header[18] = width % 256;
 	header[19] = width / 256 % 256;
 	header[20] = width / 256 / 256 % 256;
 	header[21] = width / 256 / 256 / 256 % 256;;
    
 	height = height;
 	header[22] = height &0x000000ff;
 	header[23] = (height >> 8) &0x000000ff;
 	header[24] = (height >> 16) &0x000000ff;
 	header[25] = (height >> 24) &0x000000ff;
	 	
	int file_size = width * height * bits_px/8 + 54;
 	header[2] = file_size &0x000000ff;
 	header[3] = (file_size >> 8) & 0x000000ff;
	header[4] = (file_size >> 16) & 0x000000ff;
	header[5] = (file_size >> 24) & 0x000000ff; 
	
	cout << "New Image: " << width << "x" << height << "x" << bits_px << endl;	
	
	// Write New Image
	ofstream of1("1.bmp", ios::binary);	
	of1.write((char*)&header, sizeof(header));
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			for(int k=0; k<bits_px/8; k++)
				of1.write((char*)&rgb1[i][j][k], sizeof(rgb1[i][j][k]));
	of1.close();

	
	
	
	
	
	//2  

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < bits_px / 8; k++)
			{
				rgb1[i][j][k] = original_rgb[height - 1 - i][j][k];
			}

		}

	}


 	width = width;
 	header[18] = width % 256;
 	header[19] = width / 256 % 256;
 	header[20] = width / 256 / 256 % 256;
 	header[21] = width / 256 / 256 / 256 % 256;;
    
 	height = height;
 	header[22] = height &0x000000ff;
 	header[23] = (height >> 8) &0x000000ff;
 	header[24] = (height >> 16) &0x000000ff;
 	header[25] = (height >> 24) &0x000000ff;
	 	
	file_size = width * height * bits_px/8 + 54;
 	header[2] = file_size &0x000000ff;
 	header[3] = (file_size >> 8) & 0x000000ff;
	header[4] = (file_size >> 16) & 0x000000ff;
	header[5] = (file_size >> 24) & 0x000000ff; 
	
	cout << "New Image: " << width << "x" << height << "x" << bits_px << endl;	
	
	// Write New Image
	ofstream of2("2.bmp", ios::binary);	
	of2.write((char*)&header, sizeof(header));
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			for(int k=0; k<bits_px/8; k++)
				of2.write((char*)&rgb1[i][j][k], sizeof(rgb1[i][j][k]));
	of2.close();
	
	
	//3
	int height3=height_ori*2;
	int width3=width_ori*2;
	unsigned char rgb3[height3][width3][bits_px/8];
	for (int i = 0; i < height3; i++)
	{
		for (int j = 0; j < width3; j++)
		{
			for (int k = 0; k < bits_px / 8; k++)
			{
				rgb3[i][j][k] = original_rgb[(i/2)][(j/2)][k];
			}

		}

	}


 	width =width3;
 	header[18] = width % 256;
 	header[19] = width / 256 % 256;
 	header[20] = width / 256 / 256 % 256;
 	header[21] = width / 256 / 256 / 256 % 256;;
    
 	height = height3;
 	header[22] = height &0x000000ff;
 	header[23] = (height >> 8) &0x000000ff;
 	header[24] = (height >> 16) &0x000000ff;
 	header[25] = (height >> 24) &0x000000ff;
	 	
	file_size = height3*  width3 * bits_px/8 + 54;
 	header[2] = file_size &0x000000ff;
 	header[3] = (file_size >> 8) & 0x000000ff;
	header[4] = (file_size >> 16) & 0x000000ff;
	header[5] = (file_size >> 24) & 0x000000ff; 
	
	cout << "New Image: " << width << "x" << height << "x" << bits_px << endl;	
	
	// Write New Image
	ofstream of3("3.bmp", ios::binary);	
	of3.write((char*)&header, sizeof(header));
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			for(int k=0; k<bits_px/8; k++)
				of3.write((char*)&rgb3[i][j][k], sizeof(rgb3[i][j][k]));
	of3.close();
	
	//4
	int height4=height_ori/2;
	int width4=width_ori/2;
	unsigned char rgb4[height4][width4][bits_px/8];
	for (int i = 0; i < height4; i++)
	{
		for (int j = 0; j < width4; j++)
		{
			for (int k = 0; k < bits_px / 8; k++)
			{
				rgb4[i][j][k] = original_rgb[i+(height_ori/4)][j+(width_ori/4)][k];
			}

		}

	}


 	width =width4 ;
 	header[18] = width % 256;
 	header[19] = width / 256 % 256;
 	header[20] = width / 256 / 256 % 256;
 	header[21] = width / 256 / 256 / 256 % 256;;
    
 	height =height4;
 	header[22] = height &0x000000ff;
 	header[23] = (height >> 8) &0x000000ff;
 	header[24] = (height >> 16) &0x000000ff;
 	header[25] = (height >> 24) &0x000000ff;
	 	
	file_size = width * height * bits_px/8 + 54;
 	header[2] = file_size &0x000000ff;
 	header[3] = (file_size >> 8) & 0x000000ff;
	header[4] = (file_size >> 16) & 0x000000ff;
	header[5] = (file_size >> 24) & 0x000000ff; 
	
	cout << "New Image: " << width << "x" << height << "x" << bits_px << endl;	
	
	// Write New Image
	ofstream of4("4.bmp", ios::binary);	
	of4.write((char*)&header, sizeof(header));
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			for(int k=0; k<bits_px/8; k++)
				of4.write((char*)&rgb4[i][j][k], sizeof(rgb4[i][j][k]));
	of4.close();
	


	//5
	for (int i = 0; i < height_ori; i++)
	{
		for (int j = 0; j < width_ori; j++)
		{
			for (int k = 0; k < bits_px / 8; k++)
			{
				rgb1[i][j][k] = (original_rgb[i][j][k])/2;
			}

		}

	}


 	width = width_ori;
 	header[18] = width % 256;
 	header[19] = width / 256 % 256;
 	header[20] = width / 256 / 256 % 256;
 	header[21] = width / 256 / 256 / 256 % 256;;
    
 	height = height_ori;
 	header[22] = height &0x000000ff;
 	header[23] = (height >> 8) &0x000000ff;
 	header[24] = (height >> 16) &0x000000ff;
 	header[25] = (height >> 24) &0x000000ff;
	 	
	file_size = width * height * bits_px/8 + 54;
 	header[2] = file_size &0x000000ff;
 	header[3] = (file_size >> 8) & 0x000000ff;
	header[4] = (file_size >> 16) & 0x000000ff;
	header[5] = (file_size >> 24) & 0x000000ff; 
	
	cout << "New Image: " << width << "x" << height << "x" << bits_px << endl;	
	
	// Write New Image
	ofstream of5("5.bmp", ios::binary);	
	of5.write((char*)&header, sizeof(header));
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			for(int k=0; k<bits_px/8; k++)
				of5.write((char*)&rgb1[i][j][k], sizeof(rgb1[i][j][k]));
	of5.close();

	system("pause");
	return 0;
}

