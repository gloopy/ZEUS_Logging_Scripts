#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <armadillo>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>

#define REFLAT    51.080609
#define REFLONG -114.130981


//g++ -Wall -std=c++11 Vector.cpp -o test -larmadillo {to compile}

using namespace boost::algorithm;



typedef std::vector<std::string> ArrayData;



void setMatrix(arma::mat &matrix);

int main (int argc,char** argv){


		std::ifstream inFile ("wed242016.gps");
		std::string dataline;
		std::vector<std::string> data;

		arma::mat transForm(3,3, arma::fill::zeros); //A 3x3 double's matrix stays constant for now
		arma::mat eccFVector(3,1, arma::fill::zeros);
		arma::mat ecuVector(3,1, arma::fill::zeros) ;

		


			
		std::cout << (sin(REFLONG))<< std::endl;
		
		setMatrix(transForm);


		if(inFile.is_open()){
			while(getline(inFile,dataline)){

				std::cout << std::endl;

				if(starts_with(dataline,"#BESTXYZA")){

					split(data,dataline,is_any_of(","));

					data.erase(data.begin(),data.begin()+11);


					for (ArrayData::size_type i = 0; i < 3; ++i){ //Just prints out unaltered values
						std::cout << data[i] << std::endl;
					}




					eccFVector.at(0,0) =  atof(data[0].c_str());
					eccFVector.at(1,0) =  atof(data[1].c_str());
					eccFVector.at(2,0) =  atof(data[2].c_str());

						transForm.print();



					ecuVector = transForm * eccFVector;

					std::cout << ecuVector.at(0,0) << std::endl;
					std::cout << ecuVector.at(1,0) << std::endl;
					std::cout << ecuVector.at(2,0) << std::endl;


					data.clear();

					std::cout << std::endl;


				}





			}



		}




}
//(i,j) ith row jth col 
//colums start at zero I guess nice documention  

	void setMatrix(arma::mat &matrix){

	
		try{
		matrix.at(0,0) = -1.0 * (sin (REFLONG));
		matrix.at(1,0) = -1.0 * (cos(REFLONG) * sin(REFLAT));
		matrix.at(2,0) = (cos(REFLONG)*cos(REFLAT));

		matrix.at(0,1) = -1.0* (std::cos( REFLONG ));
		matrix.at(1,1) = -1.0 * (std::sin( REFLONG )  * std::sin(REFLAT) );
		matrix.at(2,1) =  (sin(REFLONG))*(std::cos(REFLAT));

		matrix.at(0,2) =  0;
		matrix.at(1,2) =  std::cos(REFLAT);
		matrix.at(2,2) =  std::sin(REFLAT);
		
		}catch(const std::logic_error& ex){
			std::cout << "Out of bounds" << std::endl;


		}	

	}
