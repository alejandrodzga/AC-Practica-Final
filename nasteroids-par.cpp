#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <random>
#include <omp.h>
#include <ctype.h>


//libreria para entrada y salida

#include <fstream>

/* Constantes a utilizar */
#define G 0.00006674
#define dt 0.1
#define width 200.00
#define height 200.00
#define mass 1000.00
#define sdm 50.00
#define lim 200


//-----------------------------------------------------------------Clase Planeta----------------------------------------------------------------------------------// 
class planeta{
private:

double px;
double py;
double masa;
double vx;
double vy; 
public:
planeta(double px2, double py2, double masa2);
double get_px();
void set_px(double px2);

double get_py();
void set_py(double py2);

double get_masa();
void set_masa(double masa2);


};

planeta::planeta(double px2, double py2, double masa2){
        px=px2;
        py=py2;
        masa=masa2;
}

double planeta::get_px(){
	return(px);
} 

void planeta::set_px(double px2){
	px=px2;
}

double planeta::get_py(){ 
        return(py);
} 

void planeta::set_py(double py2){
        py=py2;
}

double planeta::get_masa(){ 
        return(masa);
} 

void planeta::set_masa(double masa2){
        masa=masa2;
}



//-------------------------------------------------------------------Clase asteroide-----------------------------------------------------------------------------//


class asteroide{
private:

double px;
double py;
double masa;
double vx;
double vy; 
public:
asteroide(double px2, double py2, double masa2);
double get_px();
void set_px(double px2);

double get_py();
void set_py(double py2);

double get_masa();
void set_masa(double masa2);

double get_vx();
void set_vx(double vx2);

double get_vy();
void set_vy(double vy2);

};

asteroide::asteroide(double px2, double py2, double masa2){
        px=px2;
        py=py2;
        masa=masa2;
}


double asteroide::get_px(){
        return(px);
} 

void asteroide::set_px(double px2){
        px=px2;

}

double asteroide::get_py(){ 
        return(py);
} 

void asteroide::set_py(double py2){
        py=py2;
}

double asteroide::get_masa(){ 
        return(masa);
} 

void asteroide::set_masa(double masa2){
        masa=masa2;
}

double asteroide::get_vx(){ 
        return(vx);
} 

void asteroide::set_vx(double vx2){
        vx=vx2;
}

double asteroide::get_vy(){ 
        return(vy);
} 

void asteroide::set_vy(double vy2){
        vy=vy2;
}

//--------------------------------------------------------------------------funciones---------------------------------------------------------------------------------//
// Funcion para calcular la distancia entre un planeta y un asteroide.

double distpa(planeta a, asteroide b){
        double dis;
        double pax= a.get_px();
        double pay= a.get_py();

        double pbx= b.get_px();
        double pby= b.get_py();

        double difx = pax-pbx;
        double dify = pay-pby;

        difx = pow(difx,2);
        dify = pow(dify,2);

        // No hacemos la raiz por facilitar su uso en futuras funciones
        dis= difx+dify;

        return dis;
    }

// Funcion para calcular la distancia entre asteroides 
double distaa(asteroide a, asteroide b){
        double dis;
        double pax= a.get_px();
        double pay= a.get_py();

        double pbx= b.get_px();
        double pby= b.get_py();

        double difx = pax-pbx;
        double dify = pay-pby;

        difx = pow(difx,2);
        dify = pow(dify,2);
        
        // No hacemos la raiz por facilitar su uso en futuras funciones
        dis= difx+dify;

        return dis;
    }

// Funcion que calcula el angulo que hay entre dos asteroides 
double angulopa (planeta a, asteroide b){
	double pendiente=(a.get_py()-b.get_py())/(a.get_px()-b.get_px());
	
	if(pendiente>1){
		pendiente=1;
	}
	if(pendiente<-1){
		pendiente=-1;
	}
	
	double angulo = atan(pendiente);
	return angulo;
}
// Funcion que calcula el angulo que hay entre dos asteroides 
double anguloaa (asteroide a, asteroide b){
	double pendiente=(a.get_py()-b.get_py())/(a.get_px()-b.get_px());
	
	if(pendiente>1){
		pendiente=1;
	}
	if(pendiente<-1){
		pendiente=-1;
	}
	
	double angulo = atan(pendiente);
	return angulo;
}

// Fuerza x de planeta y asteroide 
double fuerzaxpa (planeta a ,asteroide b){
	double fuerza=((G*a.get_masa()*b.get_masa())/(distpa(a,b)))*cos(angulopa(a,b));
        if(fuerza>100) fuerza=100;
	return fuerza;
}

// Fuerza y de planeta y asteroide 
double fuerzaypa (planeta a ,asteroide b){
	double fuerza=((G*a.get_masa()*b.get_masa())/(distpa(a,b)))*sin(angulopa(a,b));
        if(fuerza>100) fuerza=100;
	return fuerza;
}

// Fuerza x entre asteroides
double fuerzaxaa (asteroide a ,asteroide b){
	double fuerza=((G*a.get_masa()*b.get_masa())/( distaa(a,b)))*cos(anguloaa(a,b));
        if(fuerza>100) fuerza=100;
	return fuerza;
}

// Fuerza y entre asteroides 
double fuerzayaa (asteroide a ,asteroide b){
	double fuerza=((G*a.get_masa()*b.get_masa())/(distaa(a,b)))*sin(anguloaa(a,b));
        if(fuerza>100) fuerza=100;
	return fuerza;
}

// Funcion  calculo nueva posicion 

void actualizar(asteroide &a, double &fuerzax, double &fuerzay){
        double aceleracionx = fuerzax/a.get_masa();
        double aceleraciony = fuerzay/a.get_masa();


        double vx = a.get_vx() + aceleracionx*dt;
        double vy = a.get_vy() + aceleraciony*dt;

        a.set_vx(vx);
        a.set_vy(vy);

        double px = a.get_px() + vx*dt;
        double py = a.get_py() + vy*dt;

        a.set_px(px);
        a.set_py(py);

}


//-------------------------------------------------------------------------------main---------------------------------------------------------------------------------//


int main(int argc, char *argv[]){
        using namespace std;

        /* Casos de error en parametros */


        
        if(argc!=5){
                perror ("nasteroids-par: Wrong arguments.\nCorrect use:\nnasteroids-par num_asteroides num_iteraciones num_planetas semilla");
                return -1;
        }

        if((atoi(argv[1])<0)){
                perror ("nasteroids-par: Wrong arguments.\nCorrect use:\nnasteroids-par num_asteroides num_iteraciones num_planetas semilla");
                return -1;
        }

        if(atoi(argv[2])<0){
                perror ("nasteroids-par: Wrong arguments.\nCorrect use:\nnasteroids-par num_asteroides num_iteraciones num_planetas semilla");
                return -1;
        }

        if(atoi(argv[3])<0){ 
                perror ("nasteroids-par: Wrong arguments.\nCorrect use:\nnasteroids-par num_asteroides num_iteraciones num_planetas semilla");
                return -1;
        }

        if(atoi(argv[4])<=0){ 
                perror ("nasteroids-par: Wrong arguments.\nCorrect use:\nnasteroids-par num_asteroides num_iteraciones num_planetas semilla");
                return -1;
        }


        

        int num_asteroides=atoi(argv[1]);
        int num_iteracciones=atoi(argv[2]);
        int num_planetas=atoi(argv[3]);
        int seed=atoi(argv[4]);
 
        
        default_random_engine re{seed};
        uniform_real_distribution<double> xdist{0.0, std::nextafter(width,std::numeric_limits <double>::max())};
        uniform_real_distribution<double> ydist{0.0, std::nextafter(height,std::numeric_limits <double>::max())};
        normal_distribution<double> mdist{mass, sdm};

        vector<planeta>ps;
        vector<asteroide>as;

        int n=num_planetas/4;
        int n_mod=num_planetas%4;
	
        
        
        for(int i =0; i < num_asteroides ; i++){
		double x=xdist(re);
		double y=ydist(re);
		double m=mdist(re);
		
                asteroide aste(x,y,m);
                as.push_back(aste);
        }
        
        if(num_planetas>=4){
                for( int i = 0; i<n; i++){

			double y=ydist(re);
			double m=mdist(re);
                        planeta pa(0,y,m*10);
                        ps.push_back(pa);

			double x=xdist(re);			
			m=mdist(re);
                        planeta pb(x,0,m*10);
                        ps.push_back(pb);
			
			y=ydist(re);
			m=mdist(re);
                        planeta pc(lim,y,m*10);
                        ps.push_back(pc);

			x=xdist(re);
			m=mdist(re);
                        planeta pd(x,lim,m*10);
                        ps.push_back(pd);
			
                }
        }
        

        if(n_mod!=0){
                
                for( int i = 0; i<n_mod; i++){
				
                       		if(i==0){
					double y=ydist(re);
					double m=mdist(re);
					planeta pe(0,y,m*10);
                                        ps.push_back(pe);
                                }
				
                                else if(i==1){
					double x=xdist(re);
					double m=mdist(re);
					planeta pf(x,0,m*10);
                                        ps.push_back(pf);
                                }
				
                                else if(i==2){
					double y=ydist(re);
					double m=mdist(re);
					planeta pg(lim,y,m*10);
                                        ps.push_back(pg);
				}
    
                }   
        }

        /* Execution Setup por consola */
        cout<<"Execution setup"<<endl;
        cout<<endl;
        cout<<"Number of bodies: "<<num_asteroides<<endl;
        cout<<"Number of iterations: "<<num_iteracciones<<endl;
        cout<<"Initial file: "<<"init_conf.txt"<<endl;
        cout<<"Output file: "<<"out.txt"<<endl;
        cout<<"Number of planets: "<<num_planetas<<endl;
        cout<<"Seed: "<<seed<<endl;
        cout<<endl;
        cout<<"Number of bodies: "<<num_asteroides<<endl;
        cout<<"Gravity: "<<G<<endl;
        cout<<"Delta time: "<<dt<<endl;
        cout<<"Number of steps: "<<num_iteracciones<<endl;
        cout<<"Min. distance: "<<5<<endl;
        cout<<"Width: "<<width<<endl;
        cout<<"Height: "<<height<<endl;
        
        /* Fin Execution Setup por consola */

	/* Imprimir configuracion inicial, Ahora lo saca en un archivo .txt */
        
        ofstream fs("init_conf.txt");

        fs << num_asteroides << " " << num_iteracciones << " " << num_planetas << " " << seed << endl;
	
        if(num_asteroides!=0){
                for(auto y : as){
		        fs << setprecision(3) << fixed << y.get_px() << " " << y.get_py() << " " << y.get_masa() << endl;
	        }
        }

        if(num_planetas!=0){
	        for(auto x : ps){
		        fs << setprecision(3) << fixed << x.get_px() << " " << x.get_py() << " " << x.get_masa() << endl;
                }
	}
	/*Fin imprimir configuracion inicial */


        // Iteraciones 

        /* Creamos una copia del vector asteroides */
        vector <asteroide> as_copia;

	
        for(int i = 0; i<num_iteracciones;i++){
        	
                as_copia = as;
		#pragma omp parallel for shared(as_copia, ps, as)
                for(int j = 0; j<num_asteroides;j++){
                        double fuerza_x = 0;
                        double fuerza_y = 0;
			
                        for(int k =0; k<num_asteroides;k++){
                                
                                if(j!=k){
                                        if((sqrt(distaa(as_copia[j],as_copia[k])))<=5){
					        as[j].set_vx(as_copia[k].get_vx());
					        as[j].set_vy(as_copia[k].get_vy());
				        }
					else{
                                       		fuerza_x += fuerzaxaa(as_copia[j],as_copia[k]);
                                        	fuerza_y += fuerzayaa(as_copia[j],as_copia[k]);
					}

                                }

                       		
			}
			
                        for(int k =0; k<num_planetas;k++){
                                        fuerza_x += fuerzaxpa(ps[k],as_copia[j]);
                                        fuerza_y += fuerzaypa(ps[k],as_copia[j]);
                        }


                
                        /* Actualizamos asteroides */
                        actualizar(as[j],fuerza_x,fuerza_y);
			/*Comprobamos rebotes contra limites*/
                        
                
                        #pragma omp parallel 
                        {
			if(as[j].get_px()<=0){
				
                                as[j].set_px(5);
				as[j].set_vx(0-as[j].get_vx());
			}
 			if(as[j].get_px()>=width){
				as[j].set_px(width-5);
				as[j].set_vx(0-as[j].get_vx());
			}
			if(as[j].get_py()<=0){
				as[j].set_py(5);
				as[j].set_vy(0-as[j].get_vy());
			}
			if(as[j].get_py()>=height){
				as[j].set_py(height-5);
				as[j].set_vy(0-as[j].get_vy());
			}
                        }
                }

        }

        /* Salida de la configuracion final de los asteroides por el archivo out.txt*/
        ofstream so("out1.txt");

        if(num_asteroides!=0){
                for(auto y : as){
		        so << setprecision(3) << fixed << y.get_px() << " " << y.get_py() << " " << y.get_vx()<< " " << y.get_vy()<< " " << y.get_masa() << endl;
	        }
        }
        

        /* Fin de out.txt */
       
        

}
