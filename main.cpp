#include <bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string>

using namespace std;

int tam = 100;

int getch (void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int getche (void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

struct Banco{
    int cedula;
    string email;
    int celular;
    string clave;
    double saldo;
};
bool validarClave (string clave){
    int longitud, i;
    bool t = true;
    longitud = clave.size();
    for (i = 0; i < longitud; i++){
	    if (clave[i] < 48 || clave[i] > 57){ // Si clave no esta en ascii de los numeros 0 a 9, la clave no es numerica.
		    t = false;
            break;
	    }
    }
    return t;
}

string capturarClave (){
    int contletras;
    bool comprob = true, respuesta;
    char a;
    string clave;
    cout << "INGRESE UNA CLAVE PARA LA CUENTA: ";
    contletras = 1;
    cin.ignore();
    do{
	    a = getch(); //Este man es tan rapido que captura el enter con char en la contrasena.
	    cout << "*";
	    clave += a;
	    contletras++;
	    if (contletras == 5){
		    comprob = validarClave(clave);
		    if (comprob == false){
			    contletras = 1;
			    system("clear");
			    cout<<"\n";
            	cout << "CARACTER PROHIBIDO.\n";
        	    cout << "!VERIFICA QUE LOS DATOS SEAN CORRECTOS!.\n";
			    cout << "DIGITE NUEVAMENTE SU CONTRASENA : ";
			    clave = "";
			    cout << "\n";
		    }
	    }
    }while (contletras <= 4 || comprob == false);
    return clave;
}

int guardar (Banco c[], int tam){
    for (int i=0; i < tam; i++){
        if (c[i].cedula == 0 && c[i].email.empty() && c[i].celular == 0 && c[i].clave.empty() && c[i].saldo == 0){
            return i;
        }
    }
    return 100;
}

bool validarCedula (Banco c[], int tam, int ced){
    for (int i=0; i < tam; i++){
        if (c[i].cedula == ced){
            return true;
        }
    }
    return false;
}

void consignacion (Banco cliente[], int tam, int ced){
    bool cedulaExiste = validarCedula (cliente, tam, ced);
    if (cedulaExiste == true){
        double dineroConsignado = 0;
        string persona = "";
        system ("clear");
        cin.ignore();
        cout << "CONSIGNACIONES.\n";
        cout << "INGRESE SU NOMBRE.\n~";
        fflush(stdin);
        getline (cin, persona);
        cout << "INGRESE EL MONTO A CONSIGNAR.\n~";
        cin >> dineroConsignado;
        if (dineroConsignado >= 5000){           
            for (int i=0; i < tam; i++){
                if (cliente[i].cedula == ced){
                    cliente[i].saldo += dineroConsignado;
                    break;
                }
            }
            cout << "EL DINERO SE HA CONSIGNADO.\nGRACIAS " << persona << "POR EL DINERO.\n";
        }
        else {
            cout << "EL MONTO MINIMO ES DE $5.000.\n";
            cout << "NO PUEDE CONSIGNAR DINERO. INTENTE NUEVAMENTE.\n";
        }
    }
    else {
        cout << "LA CUENTA NO ESTA EN NUESTRO SISTEMA.\n";
    }
}

void verClientes (Banco cliente[], int tam){
    system("clear");
    cout << "A VER QUE HAY GUARDADO.\n";
    for (int i=0; i < tam; i++){
        int c = 0; 
        c = cliente[i].cedula;
        if (c != 0){                             
            cout << "\nCliente # " << i+1 << "\n";
            cout << cliente[i].cedula << "\n";
            cout << fixed;
            cout << setprecision(2) << cliente[i].celular << "\n";
            cout << cliente[i].clave<< "\n";
            cout << cliente[i].email << "\n";
            cout << "SALDO DE LA CUENTA: " << cliente[i].saldo<< "\n";
        }
        else{
            cout << "\nINGRESE MAS CLIENTES. ( # DE ESPACIOS DISPONIBLES :" << tam-i << ")\n";
            break; // Break para romper fors esta brutal.
        }
    }
    cin.get();
}

void crearCuenta (Banco cliente[], int tam){ //mmm no esta guardando datos en la struct. 9:09/10/10/2022 ya funciona
    system("clear");
    cout << "GRACIAS POR ELEGIRNOS.\n";
    cout << "COMPLETE EL FORMULARIO PARA CREAR UNA CUENTA.\n";  
    int dato = guardar(cliente, tam);
    int ced = 0;             
        if (dato >= 0 && dato < tam){    
            cout << "INGRESE EL NUMERO DE CEDULA: ";
            cin >> ced;
            if (!validarCedula(cliente, tam, ced)){
                cliente[dato].cedula = ced; 
                cout << "\nINGRESE SU EMAIL: ";
                cin >> cliente[dato].email;
                cout << "\nINGRESE SU CELULAR: ";
                cin >> cliente[dato].celular;
                cout << "\n";
                cliente[dato].clave = capturarClave();           
                cout << "\n";
                cliente[dato].saldo = 0;
            }else{
                for (int i=0; i < tam; i++){
                    if (cliente[i].cedula == ced){
                        cout << "EL USUARIO CON LA CEDULA: " << cliente[i].cedula << " YA TIENE UNA CUENTA.\n";
                        cin.ignore();
                        break;
                    }
                }
                return;
            }
        cout << "\nLA CUENTA SE HA CREADO.\n";
    }    
}

void menu(){
    int opcion = 0;
    Banco cliente[tam];
    do{
        system("clear");
            cout << "MENU BANCO.\n";
            cout << "1. CREACION DE UNA CUENTA.\n";
            cout << "2. CONSIGNACIONES.\n";
            cout << "3. CONSULTAS DE SALDO.\n";
            cout << "4. RETIROS.\n";
            cout << "5. INSCRIBIR PAGOS.\n";
            cout << "6. PAGOS.\n";
            cout << "7. CANCELACION DE LA CUENTA.\n";
            cout << "8. SALIR.\n";
            cout << "~  QUE DESEA HACER? :";
            cin >> opcion;  //Validar no ingresar letras.
        switch (opcion){
            case 1:{
                system("clear");
                int opc = 0;
                cout << "1. CREAR CUENTA.\n";
                cout << "2. VER CLIENTES.\n";
                cin >> opc;
                switch (opc){
                case 1:{
                    crearCuenta (cliente, tam);
                    break;
                }
                case 2:{
                    verClientes (cliente, tam);
                    break;
                }
                default:
                    system("clear");
                    cout << "NINGUNA OPCION DISPONIBLE FUE SELECCIONADA.\n";
                     cin.ignore();
                    // cin.get();
                    // return menu();
                    break;
                }
                cin.ignore();
                break;
            }
            case 2:{
                system("clear");
                // Funciona mostrando los datos de la struct banco en la posicion 0.
                // cout << cliente->cedula << "\n" << cliente->celular << "\n" << cliente->clave << "\n" << cliente->email << "\n" << cliente->saldo << "\n";
                int ced = 0;
                cout << "INGRESE EL NUMERO DE CEDULA A LA CUAL VA A CONSIGNAR.\n~";
                cin >> ced;
                consignacion (cliente, tam, ced);
                cin.get();
                cin.ignore();
                break;
            }
            case 3:{
                system("clear");
                cin.ignore();
                break;
            }
            case 4:{
                system("clear");
                cin.ignore();
                break;
            }
            case 5:{
                system("clear");
                cin.ignore();
                break;
            }
            case 6:{
                system("clear");
                cin.ignore();
                break;
            }
            case 7:{
                system("clear");
                cin.ignore();
                break;
            }
            case 8:{
                system("clear");
                cout << "SALIENDO....\n";
                exit(0);
                break;
            }
            default:{
                system("clear");
                cout << "NINGUNA OPCION DISPONIBLE FUE SELECCIONADA.\n";
                cin.ignore();
                return menu();
                break;
            }
        }
    }while (opcion >=1 && opcion <9);
}

void datosClean (){ //Blanquear structura en todas sus posiciones
    Banco cliente[tam];
    for (int k=0; k < tam; k++){ 
        cliente[k].cedula = 0;
        cliente[k].celular = 0;
        cliente[k].clave = "";
        cliente[k].email = "";
        cliente[k].saldo = 0;
    }  
}

int main (){
    datosClean ();
    menu ();
    cin.ignore();
    return 0;
}
