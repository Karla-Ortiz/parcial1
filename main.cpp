/*
*	autor: Karla Ortiz
* 	Clase main -> parcial I
*/
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
const char *nombre_archivo = "archivo.dat";
const char *nombre_temp = "temp.dat";

struct Empleado{
	int codigo_empleado;
	char nombres[150];
	char apellidos[150];
	char puesto[50];
	double sueldo;
	double bonificacion;
	double sueldoTotal;
};

void openFile();
void addData();
void searchData();
void deleteData();
void editData();

main(){
	int opcion=0;
	bool stop = false;
	while(!stop){
		openFile();
		cout<<"\n\n\t\t\t\t\t\t\Bienvenido al sistema"<<endl;
		cout<<"\t\t\t\t\t\t\*********************\n"<<endl;
		cout<<"\n\n\t\t\t\t\Menu de operaciones"<<endl;
		cout<<"\t\t\t\t\*******************"<<endl;
		cout<<"\t\t\t\t1.Insertar"<<endl;
		cout<<"\t\t\t\t2.Buscar"<<endl;
		cout<<"\t\t\t\t3.Eliminar"<<endl;
		cout<<"\t\t\t\t4.Modificar"<<endl;
		cout<<"\t\t\t\t5.Salir"<<endl;
		cout<<"\t\t\t\tIngresa una opcion: ";
		cin>>opcion;
		
		if(opcion == 1){
			addData();
		} else if(opcion == 2){
			searchData();
			getwchar();
			getwchar();
		} else if(opcion == 3){
			deleteData();
		} else if(opcion == 4){
			editData();
		} else if(opcion == 5){
			cout<<"Hasta luego :D"<<endl;
			stop = true; 
		}
	}
}

//Muestra la informacion que existe dentro del archivo
void openFile(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	if(!archivo){
		archivo = fopen(nombre_archivo, "w+b");
	}
	Empleado empleado;
	int id=0;
	fread(&empleado,sizeof(Empleado),1,archivo);
	cout<<"id |"<<" Codigo empleado |"<<" Nombres   |"<<" Apellidos   |"<<" Puesto   |"<<" Sueldo base   |"<<" Bonificacion   |"<<" Sueldo total   |"<<endl;
	do{
		cout<<id<<" | "<<empleado.codigo_empleado<<" | "<<empleado.nombres<<"  | "<<empleado.apellidos<<"  | "<<empleado.puesto<<"  | "<<empleado.sueldo<<"  | "<<empleado.bonificacion<<"  | "<<empleado.sueldoTotal<<endl;
		fread(&empleado,sizeof(Empleado),1,archivo);
		id+=1;
	} while(feof(archivo) ==0);
	fclose(archivo);
}

//inserta secuencialmente registros al archivo
void addData(){
	char continuar;
	FILE* archivo = fopen(nombre_archivo,"ab");
	Empleado empleado;
	string nombre, apellido, puest;
	do{
		fflush(stdin);
		cout<<"Ingrese codigo de empleado: ";
		cin>>empleado.codigo_empleado;
		cin.ignore();
		
		cout<<"Ingrese los nombres: ";
		getline(cin, nombre);
		strcpy(empleado.nombres, nombre.c_str());
		
		cout<<"Ingrese los apellidos: ";
		getline(cin, apellido);
		strcpy(empleado.apellidos, apellido.c_str());
		
		cout<<"Ingrese el puesto: ";
		getline(cin, puest);
		strcpy(empleado.puesto, puest.c_str());
		
		cout<<"Ingrese el sueldo base: ";
		cin>>empleado.sueldo;
		
		cout<<"Ingrese la bonificacion: ";
		cin>>empleado.bonificacion;
		
		empleado.sueldoTotal = empleado.sueldo+empleado.bonificacion;
		
		fwrite(&empleado,sizeof(Empleado),1,archivo);
		cout<<"Desea ingresar otro dato (s/n): ";
		cin>>continuar;
	}while(continuar=='s' || continuar=='S');
	fclose(archivo);
}

//Busca registro por medio del codigo de empleado
void searchData(){
	FILE* archivo = fopen(nombre_archivo,"rb");	
	int codigo;
	cout<<"Ingrese el Codigo de empleado: ";
	cin>>codigo;
	Empleado empleado;
	fread(&empleado,sizeof(Empleado),1,archivo);

	do{
		if(empleado.codigo_empleado == codigo){
			cout<<"______________________"<<endl;
			cout<<"Codigo de empleado: "<<empleado.codigo_empleado<<endl;
			cout<<"Nombres: "<<empleado.nombres<<endl;
			cout<<"Apellidos: "<<empleado.apellidos<<endl;
			cout<<"Puesto: "<<empleado.puesto<<endl;
			cout<<"Sueldo base: "<<empleado.sueldo<<endl;
			cout<<"Bonificacion: "<<empleado.bonificacion<<endl;
			cout<<"Sueldo total: "<<empleado.sueldoTotal<<endl;
		}
		fread(&empleado,sizeof(Empleado),1,archivo);
	} while (feof(archivo)==0);
	fclose(archivo);
}

//Elimina un registro por medio del codigo de empleado
void deleteData(){
	FILE* archivo = fopen(nombre_archivo,"r+b");
	FILE* temp = fopen(nombre_temp,"wb");
	Empleado empleado;
	int codigo = 0;
	
	cout<<"Ingrese el Codigo de empleado a eliminar:";
	cin>>codigo;
	
	while(fread(&empleado, sizeof(Empleado),1,archivo)){
		if(empleado.codigo_empleado != codigo){
			fwrite(&empleado, sizeof(Empleado),1,temp);
		}
	}
	fclose(archivo);
	fclose(temp);
	temp = fopen(nombre_temp, "r+b");
	archivo = fopen(nombre_archivo, "wb");
	while(fread(&empleado, sizeof(Empleado),1,temp)){
		fwrite(&empleado, sizeof(Empleado),1,archivo);
	}
	
	fclose(archivo);
	fclose(temp);
	remove("temp.dat");
	rename("temp.dat", "archivo.dat");
	
}

//Modifica un registro por medio del codigo de empleado
void editData(){
	FILE* archivo = fopen(nombre_archivo,"r+b");
	int id=0;
	Empleado empleado;
	string nombre,apellido, puest;
	cout<<"Ingrese el ID a Modificar:";
	cin>>id;
	fseek(archivo,id*sizeof(Empleado),SEEK_SET);
	cout<<"Modificar el Codigo:";
	cin>>empleado.codigo_empleado;
	cin.ignore();
	cout<<"Modificar Los Nombres: ";
	getline(cin,nombre);
	strcpy(empleado.nombres,nombre.c_str());
	cout<<"Modificar Los Apellidos: ";
	getline(cin,apellido);
	strcpy(empleado.apellidos,apellido.c_str());
	cout<<"Modificar El Puesto: ";
	getline(cin,puest);
	strcpy(empleado.puesto,puest.c_str());
	cout<<"Modificar el Sueldo:";
	cin>>empleado.sueldo;
	cout<<"Modifica la Bonificacion: ";
	cin>>empleado.bonificacion;
	empleado.sueldoTotal = empleado.sueldo+empleado.bonificacion;
	fwrite(&empleado,sizeof(Empleado),1,archivo);
	fclose(archivo);
}
