#include "runner.h"
#include "iomanip"
#include "cmath"
    // variable global en donde debe guardarse los datos pasados
// Esto para el calculo correcto de los siguientes pasos, distancias, calorias, etc
vector<package> storage_data = {};

// TODO: Implente esta funcion.
// Verifique que la data en el paquete sea valida
bool check_correct_data(package data) {
	return (data.segundos <= 0 || data.steps <= 0 || data.beat < 0) ? false : true;  //NUEVA VERIFICACION DE QUE EL RITMO NO SEA NEGATIVO.
}

// TODO: Implemente esta funcion.
// Verifique que el tiempo obtenido sea correcto.
bool check_correct_time(long seconds) {
	if (seconds < 0 || seconds >= 86400){
	return false;
	} if (storage_data.empty()){
		return true;
		} return (seconds > storage_data.back().segundos);
}

// TODO: Implemente esta funcion
// Devuelve la suma total de los pasos dados durante el dia
int get_step_day(int steps) {
	int total=0;
	for (const auto& i : storage_data){
	total += i.steps;
	} return total;
}

// TODO: Implemente esta funcion
// Devuelve la distancia recorrida segun los pasos dados durante el dia
double get_distance(int steps) {
  return (steps * STEP_M)/1000.0;
}

// TODO: Implemente esta funcion
// Devuelve las calorias quemadas segun la distancia recurrida
double get_calories_burned(double dist, times current_time) {
    double hours = current_time.hour + current_time.min / 60.0 + current_time.sec / 3600.0;
    double mean_speed = dist / hours;
    double minutes = hours * 60;
    double calories = (K_1 * WEIGHT + ((mean_speed*mean_speed)/HEIGHT) * K_2 * WEIGHT) * minutes;
    return calories;
}

// TODO: Implemente esta funcion
// Devuelve una string con el mensaje de motivacion segun la distancia recorrida
string get_achievement(double dist) {
   return (dist >= 6.5) ? "¡Gran entrenamiento! Objetivo cumplido."
	: (dist >= 3.9) ? "¡Nada mal! Hoy ha sido un día productivo."
	: (dist >= 2.0) ? "Menos que el resultado deseado, ¡pero intenta alcanzarlo mañana!"
	:  "Está bien tomarse el día de descanso. No siempre se puede ganar.";
}

//NUEVA FUNCION PARA MENSAJE DE RITMO CARDIACO. 
string get_message_rhythm (int rhythm){
	return (rhythm >= 161) ? "ZONA MAXIMA!! CUIDADO, BAJA LA INTENSIDAD, TU FRECUENCIA CARDIACA ESTÁ DEMASIADO ALTA."
		: (rhythm >= 141) ? "Estás trabajando ejercicios intensos para potencia, tu frecuencia cardiaca está elevada, no olvide tomar un descanso."
		: (rhythm >= 121) ? "Estás trabajando duro, tu frecuencia cardiaca está alta moderadamente."
		: (rhythm >= 101) ? "Estás trabajando ejercicios tranquilos, tu frecuencia cardiaca está moderada."
		: (rhythm >= 30) ? "Estás en reposo, tu frecuencia cardiaca está normal."
		: "TU FRECUENCIA CARDIACA ESTÁ BAJA!! SI SIENTES MAREOS, FATIGA, DOLOR AL RESPIRAR O DOLOR EN EL PECHO, BUSCA ATENCIÓN MÉDICA, PODRÍAS ESTAR SUFRIENDO UNA BRADICARDIA.";
	}

// TODO: Implemente las funciones restantes:
//       show_message
//       get_time_hms
//       format_time
times get_time_hms (long seconds){
	times time;
	time.hour = seconds / 3600;
	time.min = (seconds / 3600) / 60;
	time.sec = seconds % 60;
	return time;
}

string format_time (times t){
    string h = (t.hour < 10) ? "0" + to_string(t.hour) : to_string(t.hour);
    string m = (t.min < 10) ? "0" + to_string(t.min) : to_string(t.min);
    string s = (t.sec < 10) ? "0" + to_string(t.sec) : to_string(t.sec);
    return h + ":" + m + ":" + s;
}

void show_message (times t, int steps, double dist, double calories, string achievement, string rhythm){
     cout << fixed << setprecision(2);
     cout << "Tiempo: " << format_time(t) << "." << endl;
     cout << rhythm << endl; //NUEVO AÑADIDO
     cout << "Pasos dados hoy: " << steps << "." << endl;
     cout << "La distancia fue " << dist << " km." << endl;
     cout << "Has quemado " << calories << " cal." << endl;
     cout << achievement << endl << endl;
}




// TODO: Implemente la funcion madre
// Esta funcion debe llamar a las otras para realizar lo indicado en el pdf
vector<package> accept_package(package data) {
    if (!check_correct_data(data) || !check_correct_time(data.segundos)) {
        return storage_data;  
    }
     
    storage_data.push_back(data);
    times tiempo = get_time_hms(data.segundos);
    int pasos = get_step_day(0);
    double distancia = get_distance(pasos);
    double calorias = get_calories_burned(distancia, tiempo);
    string mensaje = get_achievement(distancia);
    string ritmo = get_message_rhythm (data.beat); //NUEVO LLAMADO DE FUNCION

    show_message(tiempo, pasos, distancia, calorias, mensaje, ritmo);
    
  return storage_data;
}