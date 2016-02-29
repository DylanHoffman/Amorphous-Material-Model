#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

void MinDistance(double a[][3],double b[][3], int n, int xlattice, int ylattice, int zlattice)
{
	ofstream outfile;
	outfile.open("minDistancees.txt");
	double ri, rj, rk, rmin[5000], distance = 0;
	int count = 0;

	cout << setw(9) << "Distances" << setw(9) << "Quantity" << endl;

	for (int i = 0; i < n-1; i++)
	{
		for (int i2 = i; i2 < n; i2++)
		{
			rmin[count] = 1000;
			for (int ni = -1; ni < 2; ni++)
			{
				for (int nj = -1; nj < 2; nj++)
				{
					for (int nk = -1; nk < 2; nk++)
					{
						ri = b[i2][0] * xlattice + ni*xlattice;
						rj = b[i2][1] * ylattice + nj*ylattice;
						rk = b[i2][2] * zlattice + nk*zlattice;
						distance = (sqrt(pow(((a[i][0] * xlattice) - ri), 2) + (pow(((a[i][1] * ylattice) - rj), 2)) + (pow(((a[i][2] * zlattice) - rk), 2))));
						if (distance < rmin[count])
						{
							rmin[count] = distance;
							
						}
					}
				}
			}
			outfile << rmin[count] << endl;
			count++;
		}
	}
	

	for (double j = 0; j < 10; j += 0.1)
	{
		int total=0;
		for (int i = 0; i < count; i++)
		{
			if (rmin[i] >= j && rmin[i] < j+ 0.1)
			{
				total++;
			}
		}
		if (total != 0)
		cout << setw(9) << j  << setw(9) <<total << endl;
	}
}

void supercell(double a[][3], int n, int nx, int ny, int nz)
{
	double supercell[1000][3];
	int count=0;
	
	for (int ni = 0; ni < nx; ni++)
	{
		for (int nj = 0; nj < ny; nj++)
		{
			for (int nk = 0; nk < nz; nk++)
			{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						
						supercell[i][j] = a[i][j];
						cout << supercell[i][j] << endl;
						count++;
					}
				}
			}
		}
	}
	cout << count;
}




int main()
{
	ifstream infile;
	string filename;
	double ri, rj, rk, rmin = 1000, Sir[1000][3], Cr[1000][3], distance = 0;
	double xlattice, ylattice, zlattice, multiplier;
	char skip1, skip2, skip3;
	double s;
	int n, Si, C;

	cout << "Enter the filename: ";
	cin >> filename;
	infile.open(filename);

	if (!infile)
	{
		cout << "File is not found" << endl;
	}
	else
	{
		infile >> multiplier >> xlattice >> ylattice >> zlattice >> skip1 >> skip2 >> skip3 >> Si >> C;
		

		for (int i = 0; i < Si; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				infile >> Sir[i][j];
			}
			for (int i = 0; i < 3; i++)
			{
				infile >> skip1;
			}
		}

		for (int i = 0; i < C; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				infile >> Cr[i][j];
			}
			for (int i = 0; i < 3; i++)
			{
				infile >> skip1;
			}
		}
		cout << "Min distance between Carbon Atoms:" << endl;
		MinDistance(Cr, Cr, 64, xlattice, ylattice, zlattice);
		cout << endl;
		cout << "Min distance between Carbon and Silicon Atoms:" << endl;
		MinDistance(Sir, Cr, 64, xlattice, ylattice, zlattice);
		cout << endl;
		cout << "Min distance between Silicon Atoms:" << endl;
		MinDistance(Sir, Sir, 64,  xlattice, ylattice, zlattice);
		cout << endl;
		
	}
}