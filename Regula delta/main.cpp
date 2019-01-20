#include<iostream>
#include<cmath>

double beta = 4.0;

double f(double s)
{
	return(1.0 - exp(-beta * s)) / (1.0 + exp(-beta * s));
}

int main() {
	//wartosci 

	//jedynka
	double taby1[13] = { 1.0,-1.0,-1.0,1.0,-1.0,-1.0,1.0,-1.0,-1.0,1.0,-1.0,-1.0,1.0};	
	
	//czworka
	double taby4[13] = { 1.0, 1.0,-1.0,1.0,1.0,1.0,1.0,-1.0,-1.0,1.0,-1.0,-1.0,1.0 };
	
	//siodemka
	double taby7[13] = { 1.0,1.0,1.0,1.0,-1.0,-1.0,1.0,-1.0,-1.0,1.0,-1.0,-1.0,1.0 };
	
	//macierz W o rozmiarze K x J
	double tabd[3][2] = {{1.0,1.0},
						 {1.0, -1.0},
						 {-1.0, 1.0}
						};

	//wspó³czynnik uczenia
	double ni = 0.6;

	// b³ad	
	double Emax=0.0;	
	double tabE[6];

	//przypisanie wag poczatkowych
	double wx1[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double wx2[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double wx3[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double wx4[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double wx5[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double wx6[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };	
	
	int d = 0; //kroki programu
	do {	
		//wartosci poczatkowe dla sumy i wartosci funkcji
		double sum = 0.0;
		double zk = 0.0;
		double zk2 = 0.0;
		double zk3 = 0.0;
		double zk4 = 0.0;
		double zk5 = 0.0;
		double zk6 = 0.0;

		//neutron 1		
		for (int i = 0; i < 13; i++) {
			sum = sum + taby1[i] * wx1[i];
			zk = f(1 * sum);
			wx1[i] = wx1[i] + (0.5)*ni*(tabd[0][0] - zk)*(1 - zk * zk)*taby1[i];	
			tabE[0] = (0.5)*((tabd[0][0] - zk)*(tabd[0][0] - zk));
			d++;
		}

		//neutron 2
		sum = 0;		
		for (int i = 0; i < 13; i++)
		{
			sum = sum + taby1[i] * wx2[i];
			zk2 = f(1 * sum);
			wx2[i] = wx2[i] + (0.5)*ni*(tabd[0][1] - zk2)*(1 - zk2 * zk2)*taby1[i];
			tabE[1] = (0.5)*((tabd[0][1] - zk2)*(tabd[0][1] - zk2));
			d++;
		}
		//neutron 1
		sum = 0;
		for (int i = 0; i < 13; i++)
		{
			sum = sum + taby4[i] * wx3[i];
			zk3 = f(2 * sum);
			wx3[i] = wx3[i] + (0.5)*ni*(tabd[1][0] - zk3)*(1 - zk3 * zk3)*taby4[i];
			tabE[2] = (0.5)*((tabd[1][0] - zk3)*(tabd[1][0] - zk3));	
			d++;
		}

		//neutron 2
		sum = 0;
		for (int i = 0; i < 13; i++)
		{
			sum = sum + taby4[i] * wx4[i];
			zk4 = f(2 * sum);
			wx4[i] = wx4[i] + (0.5)*ni*(tabd[1][1] - zk4)*(1 - zk4 * zk4)*taby4[i];
			tabE[3] = (0.5)*((tabd[1][1] - zk4)*(tabd[1][1] - zk4));
			d++;
		}

		//neutron 1
		sum = 0;
		for (int i = 0; i < 13; i++)
		{
			sum = sum + taby7[i] * wx5[i];
			zk5 = f(3 * sum);
			wx5[i] = wx5[i] + (0.5)*ni*(tabd[2][0] - zk5)*(1 - zk5 * zk5)*taby7[i];
			tabE[4] = (0.5)*((tabd[2][0] - zk5)*(tabd[2][0] - zk5));
			d++;
		}

		//neutron 2
		sum = 0;
		for (int i = 0; i < 13; i++)
		{
			sum = sum + taby7[i] * wx6[i];
			zk6 = f(3 * sum);
			wx6[i] = wx6[i] + (0.5)*ni*(tabd[2][1] - zk6)*(1 - zk6 * zk6)*taby7[i];
			tabE[5] = (0.5)*((tabd[2][1] - zk6)*(tabd[2][1] - zk6));
			d++;
		}
		//suma bledow
		Emax = tabE[0] + tabE[1] + tabE[2] + tabE[3] + tabE[4] + tabE[5];
		d++;
		if (Emax < 0.03) {
			std::cout << "Wynik dla jedynki: " << zk << "  " << zk2 << std::endl;
			std::cout << "Wynik dla czworki: " << zk3 << "  " << zk4 << std::endl;
			std::cout<< "Wynik dla siodemki: " << zk5 << "  " << zk6 << std::endl;
			std::cout << "Kroki programu: " << d << std::endl;
		}
	} while (Emax > 0.03);

	system("pause");
	return 0;
}