<?php

/**
* @file
* Callbacks de administración del módulo saludar.
*/
/**
* Define el formulario de opciones de configuración.
*/

function birthday_configuracion() {
        $form['felicitar_cumpleaños'] = array(
          '#type' => 'date',  //tipo fecha
          '#title' => "Fecha de nacimiento", 
          '#after_build' => array("birthday_formato")
        );

 $form['submit'] = array(
	'#type' => 'submit',
	'#value' => 'Guardar configuración',
 );
 
 $form['#submit'][] = 'birthday_configuracion_submit';
 return $form;
 
}

function birthday_formato($form_element, &$form_state){

    unset($form_element['year']['#options']);

    //Ponemos el rango que queramos establecer
    $max_age = date('Y') - 100; 
    $min_age = date('Y') - 7; 
    
    //Llenamos el vector
    $form_element['year']['#options'] = array();
	
    foreach (range($max_age, $min_age) as $year){
	
        $form_element['year']['#options'][$year] = $year;
		
    }
    
    // Devolvemos la variable ya modificada
    return $form_element;
}

/**
* Valida el formulario de opciones de configuración.
*/

function birthday_configuracion_validate($form, &$form_state) {

 if (empty($form))
 
	form_set_error('felicitar_cumpleaños', 'El campo felicitación no puede quedar vacío.'); //Se comprueba si está vacío.
	
 else{
 
	date_default_timezone_set("Europe/Paris");
	$fecha_actual = date('Y/m/d');
	$fecha_cumpleanos = $form_state['values']['felicitar_cumpleaños'];
	$fecha_admin = $fecha_cumpleanos['year'].'/'.$fecha_cumpleanos['month'].'/'.$fecha_cumpleanos['day'];
	
	if (strtotime($fecha_admin) - strtotime ($fecha_actual) > 0 )   // Se comprueba si la fecha seleccionada es una fecha futura.
	
		form_set_error('felicitar_cumpleaños', 'La fecha introducida es una fecha futura.');
		
 }
}
/**
* Procesa el envío del formulario de opciones de configuración.
*/
function birthday_configuracion_submit($form, $form_state) {

 variable_set('fecha_cumpleanos',$form_state['values']['felicitar_cumpleaños']);
 drupal_set_message("Se han guardado las opciones de configuración.");
 
}