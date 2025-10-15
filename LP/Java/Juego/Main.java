package Juego;

import Juego.player.Jugador;
import Juego.entorno.Zonas;
//import Juego.objetos.ItemTipo;

import java.util.Scanner;


public class Main {
    static Jugador jugador;
    static Zonas zonas; 
    public static void main(String[] args) {
        mensajeBienvenida();
        Jugador jugador = CrearMundo();
        cicloJuego(jugador, jugador.getZonas());
    }

    public static Jugador CrearMundo() {
         //crea al jugador y las zonas
        return new Jugador(); //las zonas se crean en el constructor del jugador
    }



    public static void cicloJuego(Jugador jugador, Zonas zonas) {
        //metodo que controla el ciclo del juego
        Scanner scanner = new Scanner(System.in);
        
        boolean juegoActivo = true;

        while (juegoActivo){
            if (jugador.isEnNaveExploradora()){
                //opciones de la nave
                opcionesNaveExploradora(scanner , jugador , zonas);
            } else if (jugador.getZonaActual().getNombre() == "Nave Estrellada"){
                //opciones de la nave estrellada
                opcionesNaveEstrellada(scanner , jugador , zonas);
            }
            else {
                //opicones del agua
                opcionesAgua(scanner, jugador, zonas);
            }
        }
        scanner.close(); // cierro el scanner, aparentemente es algo que hay que hacer
    }
    
    public static void opcionesNaveExploradora(Scanner scanner , Jugador jugador , Zonas zonas) {
        jugador.getTanqueOxigeno().recargarCompleto(); // recargar oxigeno
                System.out.println("Estás en la nave exploradora. ¿Qué deseas hacer?\n");
                System.out.println("1. Subir o desecender\n");
                System.out.println("2. Gestionar inventario\n");
                System.out.println("3. Crear Objetos\n");
                System.out.println("4. Ir a otra zona\n");
                System.out.println("5. Salir de la nave\n");
                System.out.println("6. Ver estado del jugador\n");
                int opcion = scanner.nextInt();
                switch (opcion) {
                    case 1:
                        //subir o descender
                        System.out.println("Profundidad actual: " + jugador.getProfundidadActual() + " metros.");
                        System.out.println("Ingresa la nueva profundidad a la que deseas ir:");
                        int nuevaProfundidad = scanner.nextInt();
                        jugador.getNave().accederProfundidad(jugador, nuevaProfundidad);
                        break;
                    case 2:
                        //gestionar inventario
                        System.out.println("Este es tu inventario\n");
                        jugador.mostrarInventario();
                        System.out.println("Este es el inventario de la nave exploradora\n");
                        jugador.getNave().mostrarInventario();
                        System.out.println("¿Qué deseas hacer?\n");
                        System.out.println("1. Guardar objetos en la nave exploradora\n");
                        System.out.println("2. Sacar objetos de la nave exploradora\n");
                        int opcionInventario = scanner.nextInt();
                        switch (opcionInventario) {
                            case 1:
                                jugador.guardarEnNave(scanner);
                                break;
                            case 2:
                                jugador.sacarDeNave(scanner);
                                break;
                            default:
                                System.out.println("Opcion no valida. Ingresa 1 o 2.");
                                break;
                        }
                        break;
                    case 3:
                        //crear objetos
                        System.out.println("¿Qué deseas crear?\n");
                        System.out.println("1. Mejora de tanque de oxígeno (requiere 3 piezas del tanque de oxígeno)\n");
                        System.out.println("2. Mejora oxigeno (requiere la mejora del tanque , 10*PLATA y 5*CUARZO)\n");
                        System.out.println("3. Traje térmico (requiere 10*SILICIO 3*ORO y 5*CUARZO)\n");
                        System.out.println("4. instalar Modulo de profundidad (requiere haber encontrado el Modulo Profundidad)\n");
                        System.out.println("5. Robot Excavador (crearlo, mejorarlo y repararlo )\n");
                        int opcion2 = scanner.nextInt();
                        switch (opcion2) {
                            case 1:
                                jugador.crearMejoraTanque();
                                break;
                            case 2:
                                jugador.mejorarOxigeno();
                                break;
                            case 3:
                                jugador.crearTrajeTermico();
                                break;
                            case 4:
                                jugador.instalarModuloProfundidad();
                                break;
                            case 5:
                                //opciones del robotExcavador
                                System.out.println("Has descubierto una mecanica no implementada en el juego, felicidades!!");
                                break;
                            default:
                                break;
                        }
                        break;
                    case 4:
                        //ir a otra zona
                        System.out.println("Zonas disponibles:");
                        System.out.println("1. Zona Arrecife (1-199 metros)");
                        System.out.println("2. Zona Profunda (200-999 metros)");
                        System.out.println("3. Zona Volcanica (1000-1500 metros)");
                        System.out.println("Ingresa el numero de la zona a la que deseas ir:");
                        int zonaElegida = scanner.nextInt();

                        switch (zonaElegida) {
                            //case 0:
                                //if (jugador.getNave().puedeAcceder(0))  {
                                //jugador.setZonaActual(zonas.getNaveEstrellada());
                                //jugador.getNave().setProfundidadActual(0);
                                //System.out.println("Has entrado a la Nave Estrellada.");
                                //}     //(no puedes entrar a la naveEstrellada con la naveExploradora)
                                //break;
                            case 1:
                                if (jugador.getNave().puedeAcceder(1)){
                                jugador.setZonaActual(zonas.getArrecife());
                                jugador.getNave().setProfundidadActual(1);
                                System.out.println("Has entrado a la Zona Arrecife.");
                                }
                                break;
                            case 2:
                                if (jugador.getNave().puedeAcceder(200)){
                                jugador.setZonaActual(zonas.getProfunda());
                                jugador.getNave().setProfundidadActual(200);
                                System.out.println("Has entrado a la Zona Profunda.");
                                }
                                break;
                            case 3:
                                if (jugador.getNave().puedeAcceder(1000)){
                                jugador.setZonaActual(zonas.getVolcanica());
                                jugador.getNave().setProfundidadActual(1000);
                                System.out.println("Has entrado a la Zona Volcanica.");
                                } else {System.out.println("Mejora el MODULO PROFUNDIDAD para acceder a esta zona");}
                                break;
                            default:
                                System.out.println("Opcion no valida. Ingresa un numero del 0 al 3.");
                                break;
                        }
                    
                    break;
                    case 5:
                        //salir de la nave
                        jugador.saliroEntrarNave();
                        break;
                    case 6:
                        jugador.verEstadoJugador();
                        break;
                    default:
                        System.out.println("Opcion no valida. Ingresa un numero del 1 al 6.");
                        break;
                }
    }

    public static void opcionesAgua(Scanner scanner , Jugador jugador , Zonas zonas) {
        System.out.println("Estás en el agua. ¿Qué deseas hacer?\n");
                System.out.println("1. Subir o descender\n");
                System.out.println("2. Recolectar recursos\n");
                System.out.println("3. Explorar la zona\n");
                System.out.println("4. Volver a la nave exploradora\n");
                System.out.println("5. Cambiar de zona a Nado (solo posible en los limites de Zona)\n");
                System.out.println("6. Ver estado del jugador\n");
                int opcion = scanner.nextInt();
                switch (opcion) {
                    case 1:
                        //subir o descender
                        System.out.println("Profundidad actual: " + jugador.getProfundidadActual() + " metros.");
                        System.out.println("Ingresa la nueva profundidad a la que deseas ir:");
                        int nuevaProfundidad = scanner.nextInt();
                        jugador.accederProfundidad(jugador, nuevaProfundidad);
                        break;
                    case 2:
                        //recolectar recursos
                        System.out.println("Recolectando recursos...");
                        jugador.getZonaActual().recolectarRecursos(jugador);
                        break;
                    case 3:
                        //explorar la zona
                        System.out.println("Explorando la zona...");
                        jugador.getZonaActual().explorar(jugador);
                        break;
                    case 4:
                        //volver a la nave
                        jugador.saliroEntrarNave();
                        break;
                    case 5:
                        //cambia a la zona de arriba o abajo
                        jugador.cambiarZonaANado();
                        break;
                    case 6:
                        jugador.verEstadoJugador();
                        break;
                    default:
                        System.out.println("Opcion no valida. Ingresa un numero del 1 al 5.");
                        break;
                }
    }

    public static void opcionesNaveEstrellada(Scanner scanner , Jugador jugador , Zonas zonas){
        /**
         * una solo accion si no se tiene el traje termico (recolectar o explorar, al turno siguiente se debe salir o te mueres)
         * opcion 1: salir de la nave estrellada
         * opcion 2: recoletar recursos
         * opcion 3: explorar la zona
         * opcion 4: reparar la nave estrellada (si se tienen los recursos)
         * opcion 5: ver estado del jugador
         */
        if (!jugador.getTrajeTermico()){
            System.out.println("La Nave esta en llamas!, solo puedes recolectar recursos o explorar la zona. Después debes salir de la nave estrellada.");
            System.out.println("1. Recolectar recursos\n");
            System.out.println("2. Explorar la zona\n");
            System.out.println("3. Salir de la nave estrellada\n");
            int opcion = scanner.nextInt();
            switch (opcion) {
                case 1:
                    //recolectar recursos
                    System.out.println("Recolectando recursos...");
                    jugador.getZonaActual().recolectarRecursos(jugador);
                    break;
                case 2:
                    //explorar la zona
                    System.out.println("Explorando la zona...");
                    jugador.getZonaActual().explorar(jugador);
                    break;
                case 3:
                    //salir de la nave estrellada
                    System.out.println("Saliendo...");
                    jugador.setZonaActual(jugador.getZonas().getArrecife());
                    break;    
                default:
                    System.out.println("Opcion no valida. Ingresa 1 o 2.");
                    break;
            }
            System.out.println("Sal ahora si no quieres morir de calor.");
            System.out.println("1. Recolectar recursos\n");
            System.out.println("2. Explorar la zona\n");
            System.out.println("3. Salir de la nave estrellada\n");
            int opcion2 = scanner.nextInt();
            switch (opcion2) {
                case 1:
                    jugador.matarJugador();
                    break;
                case 2:
                    jugador.matarJugador();
                    break;
                case 3:
                    //salir de la nave estrellada
                    System.out.println("Saliendo...");
                    jugador.setZonaActual(jugador.getZonas().getArrecife());
                    break;
        }
    } else {
            System.out.println("Estás en la nave estrellada. ¿Qué deseas hacer?\n");
            System.out.println("1. Salir de la nave estrellada\n");
            System.out.println("2. Recolectar recursos\n");
            System.out.println("3. Explorar la zona\n");
            System.out.println("4. Reparar la nave estrellada (si tienes los recursos)\n");
            System.out.println("5. Ver estado del jugador\n");
            int opcion = scanner.nextInt();
            switch (opcion) {
                case 1:
                    //salir de la nave estrellada
                    System.out.println("Saliendo...");
                    jugador.setZonaActual(jugador.getZonas().getArrecife());
                    break;
                case 2:
                    //recolectar recursos
                    System.out.println("Recolectando recursos...");
                    jugador.getZonaActual().recolectarRecursos(jugador);
                    break;
                case 3:
                    //explorar la zona
                    System.out.println("Explorando la zona...");
                    jugador.getZonaActual().explorar(jugador);
                    break;
                case 4:
                    //reparar la nave estrellada
                    System.out.println("Reparando la nave estrellada...");
                    jugador.repararNaveEstrellada();
                    break;
                case 5:
                    jugador.verEstadoJugador();
                    break;
                default:
                    System.out.println("Opcion no valida. Ingresa un numero del 1 al 5.");
                    break;
            }
        }
    }

    public static void finalDelJuego(){
        System.out.println("¡Felicidades! Has reparado la nave estrellada y completado el juego.");
        System.exit(0); // termina el programa
    }

    public static void mensajeBienvenida(){
        System.out.println("Eras un defensor del espacio, pero tu nave fue gravemente dañada por unos alienigenas");
        System.out.println("Lograste hacer un acuatizaje forzoso en un planeta desconocido, solo ves oceano en todas las direcciones");
        System.out.println("Tu objetivo es encontrar los planos para reparar tu nave y poder salir de este misterioso planeta");
        System.out.println("Explora las profundidades del oceano, obten valiosos recursos, mejora tu equipamiento y recuerda respirar");
        System.out.println("¡Buena suerte!");

    }
}