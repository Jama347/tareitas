package Juego.player;

import Juego.objetos.NaveExploradora;
import Juego.objetos.Item;
import Juego.objetos.AccesoProfundidad;
import Juego.objetos.ItemTipo;
import Juego.entorno.Zona;
import Juego.entorno.Zonas;
import Juego.Main;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


public class Jugador implements AccesoProfundidad {
    private Oxigeno tanqueOxigeno;
    private List<Item> inventario;
    private Zona zonaActual;
    private int profundidadActual;
    private boolean tienePlanos;
    private NaveExploradora nave;
    private boolean trajeTermico;
    private byte cantPiezasTanque;
    private boolean mejoraTanque;
    private boolean enNaveExploradora;
    private Zonas zonas = new Zonas();

    public Jugador() {
        this.tanqueOxigeno = new Oxigeno();
        this.inventario = new ArrayList<>();
        this.zonas = new Zonas(); // Inicializa las zonas
        this.zonaActual = zonas.getArrecife(); // Se inicializa en la Zona Arrecife.
        this.profundidadActual = 1;
        this.tienePlanos = false;
        this.nave = new NaveExploradora();
        this.trajeTermico = false;
        this.cantPiezasTanque = 0;
        this.mejoraTanque = false;
        this.enNaveExploradora = true;
    }

    public void verEstadoJugador() {
        System.out.println("Oxígeno restante: " + tanqueOxigeno.getOxigenoRestante() + "/" + tanqueOxigeno.getCapacidadMaxima());
        System.out.println("Zona actual: " + (zonaActual != null ? zonaActual.getNombre() : "Nave Exploradora"));
        System.out.println("Profundidad actual: " + profundidadActual + " metros");
        System.out.println("Inventario: ");
        if (inventario.isEmpty()) {
            System.out.println("  (vacío)");
        } else {
            for (Item item : this.inventario) {
                System.out.println("  - " + item.getTipo().name() + " (x" + item.getCantidad() + ")");
            }
        }
        System.out.println("Traje térmico: " + (trajeTermico ? "Sí" : "No"));
        System.out.println("Mejora de tanque de oxígeno: " + (mejoraTanque ? "Sí" : "No"));
    }
    public void matarJugador() {
        //metodo que mata al jugador
        System.out.println("Has muerto. Regresas a la nave exploradora.");
        this.enNaveExploradora = true;
        this.zonaActual = this.zonas.getZonaPorProfundidad(this.nave.getProfundidadActual());
        this.profundidadActual = this.nave.getProfundidadActual();
        this.tanqueOxigeno.recargarCompleto();
        inventario.clear();
    }

    //metodos relacionados con la nave
    public boolean isEnNaveExploradora() {
        return enNaveExploradora;
    }
    public void saliroEntrarNave() {
        //sale si estas dentro y entra si estas fuera
        if (getProfundidadActual() == getNave().getProfundidadActual()) {
            this.enNaveExploradora = !this.enNaveExploradora;
            return;
        } else {
            System.out.println("No puedes entrar o salir de la nave en la profundidad actual.");
            System.out.println("Profundidad nave: " + getNave().getProfundidadActual() + " metros, Profundidad jugador: " + getProfundidadActual() + " metros.");
        }
        
    }
    public NaveExploradora getNave() {
        return nave;
    }

    //metodos relacionados con las mejoras
    public byte getCantPiezasTanque() {
        return cantPiezasTanque;
    }
    public void setCantPiezasTanque(byte cantPiezasTanque) {
        this.cantPiezasTanque = cantPiezasTanque;
    }
    public void incrementarCantPiezasTanque() {
        if (cantPiezasTanque < 3) {
            this.cantPiezasTanque++;
        }
    }
    public boolean getMejoraTanque() {
        return mejoraTanque;
    }
    public void setMejoraTanque(boolean mejoraTanque) {
        this.mejoraTanque = mejoraTanque;
    }
    public boolean getTienePlanos() {
        return tienePlanos;
    }
    public void setTienePlanos(boolean tienePlanos) {
        this.tienePlanos = tienePlanos;
    }
    public boolean getTrajeTermico() {
        return trajeTermico;
    }
    public void setTrajeTermico(boolean trajeTermico) {
        this.trajeTermico = trajeTermico;
    }

    //metodos relacionados al tanque de oxigeno
    public Oxigeno getTanqueOxigeno() { //getter para el tanque de oxigeno
        return tanqueOxigeno;
    }
    public int getProfundidadActual() {
        return profundidadActual;
    }

    //metodos relacionados con la Zona
    public Zonas getZonas() {
        return zonas;
    }
    public Zona getZonaActual() {
        return zonaActual;
    }
    public void setZonaActual(Zona zona) {
        this.zonaActual = zona;
        this.profundidadActual = zona.getProfundidadMin(); // Al entrar a una zona, se inicia en la profundidad minima
    }
    public boolean puedeAcceder(int profundidad) {
        // con ambas mejoras puede acceder a cualquier profundidad, si no, solo sobre la ZonaVolcanica
        return (this.mejoraTanque && this.trajeTermico )|| profundidad <= 1000 ;
    }
    public void recursosAleatorios(int cantidad){
        //saca recursos aleatorios de la zona actual y los guarda en el inventario
        if (this.zonaActual != null) {
            List<ItemTipo> recursosDisponibles = new ArrayList<>(this.zonaActual.getRecursos());
            for (int i = 0; i < cantidad; i++) {
                int indiceAleatorio = (int) (Math.random() * recursosDisponibles.size());
                ItemTipo recurso = recursosDisponibles.get(indiceAleatorio);
                agregarItemInventario(recurso);
            }
        } else {
            System.out.println("No estás en una zona para recolectar recursos.");
        }
    }
    public void cambiarZonaANado(){
        //permite cambiar de zona nadando, solo entre las zonas que estan conectadas
        switch (this.getZonaActual().getNombre()) { //nombre de la zona actual
            case "Zona Arrecife":
                if (this.getProfundidadActual() == 1) { //subir
                    this.setZonaActual(zonas.getNaveEstrellada());
                } else if (this.getProfundidadActual() == 199) { //bajar
                    Zonas zonas = new Zonas();
                    this.setZonaActual(zonas.getProfunda());
                } else {
                    System.out.println("debes estar en la altura maxima o minima de la zona para cambiar a otra.");
                }
                break;
            case "Zona Profunda":
                if (this.getProfundidadActual() == 200){ //subir
                    this.setZonaActual(zonas.getArrecife());
                } else if (this.getProfundidadActual() == 999){ //bajar
                    Zonas zonas = new Zonas();
                    this.setZonaActual(zonas.getVolcanica());
                } else {
                    System.out.println("debes estar en la altura maxima o minima de la zona para cambiar a otra.");
                }
            default:
                break;
        }
    }

    //metodos relacionados con el inventario
    public List<Item> getInventario() {
        return inventario;
    }
    public void agregarItemInventario(ItemTipo tipo) {
        //agrega un item al inventario 
        for (Item item : inventario) {
            if (item.getTipo() == tipo) {
                item.setCantidad(item.getCantidad() + 1);
                System.out.println("Se ha agregado " + tipo + " al inventario. Cantidad actual: " + item.getCantidad());
                return;
            }
        }
        inventario.add(new Item(tipo, 1));
        System.out.println("Se ha agregado " + tipo + " al inventario. Cantidad actual: 1");
    }
    public void guardarEnLaNave(ItemTipo tipo , int cantidad){
        //toma items del invetario del jugador y los pone en la naveExploradora
        this.getNave().transferirObjetos(tipo , cantidad , this.inventario , this.getNave().getInventario());
    }
    public void sacarDeLaNave(ItemTipo tipo , int cantidad){
        //toma items de la naveExploradora y los pone en el inventario del jugador
        this.getNave().transferirObjetos(tipo , cantidad , this.getNave().getInventario() , this.inventario);
    }
    public void mostrarInventario(){
        //muestra por pantalla el inventario del jugador, de la forma que se ve en verEstadoJugador
        System.out.println("Inventario: ");
        if (inventario.isEmpty()) {
            System.out.println("  (vacío)");
        } else {
            for (Item item : this.inventario) {
                System.out.println("  - " + item.getTipo().name() + " (x" + item.getCantidad() + ")");
            }
        }
    }
    public void guardarEnNave(Scanner scanner){
        System.out.println("¿Deseas guardar objetos en la nave exploradora? (s/n)");
        char respuesta = scanner.next().toLowerCase().charAt(0);
        if (respuesta == 's') {
            System.out.println("Ingresa el tipo de objeto que deseas guardar (por ejemplo, ORO, PLATA, etc.):");
            String tipoStr = scanner.next().toUpperCase();
            ItemTipo tipo;
            try {
                tipo = ItemTipo.valueOf(tipoStr);
            } catch (IllegalArgumentException e) {
                System.out.println("Tipo de objeto no válido.");
                return;
            }
            System.out.println("Ingresa la cantidad que deseas guardar:");
            int cantidad = scanner.nextInt();
            this.guardarEnLaNave(tipo, cantidad);
            } else {
                System.out.println("No se han guardado objetos en la nave.");
            }
        }
    public void sacarDeNave(Scanner scanner){
        System.out.println("¿Deseas sacar objetos de la nave exploradora? (s/n)");
        char respuesta = scanner.next().toLowerCase().charAt(0);
        if (respuesta == 's') {
            System.out.println("Ingresa el tipo de objeto que deseas sacar (por ejemplo, ORO, PLATA, etc.):");
            String tipoStr = scanner.next().toUpperCase();
            ItemTipo tipo;
            try {
                tipo = ItemTipo.valueOf(tipoStr);
            } catch (IllegalArgumentException e) {
                System.out.println("Tipo de objeto no válido.");
                return;
            }
            System.out.println("Ingresa la cantidad que deseas sacar:");
            int cantidad = scanner.nextInt();
            this.sacarDeLaNave(tipo, cantidad);
            } else {
                System.out.println("No se han sacado objetos de la nave.");
            }
        }

    //metodos relacionados con la profundidad
    public void accederProfundidad(Jugador jugador, int nuevaProfundidad) {
        // hay que chequear la nueva profundidad esta dentro del rango de la zona actual
        if (jugador.getZonas().getZonaPorProfundidad(nuevaProfundidad) == jugador.getZonas().getZonaPorProfundidad(this.profundidadActual)) {
            System.out.println("No puedes acceder a esa profundidad en la zona actual. Rango permitido: " + this.zonaActual.getProfundidadMin() + " - " + this.zonaActual.getProfundidadMax() + " metros.");
            return;
        }
        if (puedeAcceder(nuevaProfundidad)) {
            jugador.getTanqueOxigeno().consumirOxigeno(jugador.getTanqueOxigeno().consumoMover(jugador, nuevaProfundidad), this); // Consumir oxígeno al cambiar de profundidad
            setProfundidadActual(nuevaProfundidad);
            System.out.println("Jugador descendió a una profundidad de " + nuevaProfundidad + " metros.");
        } else {
            System.out.println("No puedes acceder a esa profundidad. Profundidad máxima permitida: 1000 metros sin mejoras.");
        }
    }

    public void setProfundidadActual(int profundidadActual) {
        this.profundidadActual = profundidadActual;
    }

    //metodos relacionados al crafteo
    public void crearMejoraTanque(){
        if (this.cantPiezasTanque >= 3 && !this.mejoraTanque) {
            this.mejoraTanque = true;
            this.cantPiezasTanque = 0; // Reinicia las piezas después de crear la mejora
            this.tanqueOxigeno.aumentarCapacidad(60); // Aumenta la capacidad del tanque en un 100%
            System.out.println("¡Mejora del tanque de oxígeno creada! Nueva capacidad: " + this.tanqueOxigeno.getCapacidadMaxima());
        } else if (this.mejoraTanque) {
            System.out.println("Ya tienes la mejora del tanque de oxígeno.");
        } else {
            System.out.println("No tienes suficientes piezas para crear la mejora del tanque de oxígeno. Necesitas 3 piezas.");
        }
    }
    public void mejorarOxigeno(){
        // requiere tener la mejora del tanque y ocupa 10*PLATA y 5*CUARZO
        // extrae los recursos de la bodega de la naveExploradora
        if (this.mejoraTanque) {
            int plataNecesaria = 10;
            int cuarzoNecesario = 5;
            int plataDisponible = 0;
            int cuarzoDisponible = 0;

            // Contar plata y cuarzo en la bodega de la nave
            for (Item item : this.getNave().getInventario()) {
                if (item.getTipo() == ItemTipo.PLATA) {
                    plataDisponible = item.getCantidad();
                } else if (item.getTipo() == ItemTipo.CUARZO) {
                    cuarzoDisponible = item.getCantidad();
                }
            }

            if (plataDisponible >= plataNecesaria && cuarzoDisponible >= cuarzoNecesario) {
                // Extraer los recursos necesarios
                this.getNave().transferirObjetos(ItemTipo.PLATA, plataNecesaria, this.getNave().getInventario(), new ArrayList<>());
                this.getNave().transferirObjetos(ItemTipo.CUARZO, cuarzoNecesario, this.getNave().getInventario(), new ArrayList<>());

                // Aumentar la capacidad del tanque
                this.tanqueOxigeno.aumentarCapacidad(30); // Aumenta la capacidad en 30 unidades
                System.out.println("¡Capacidad del tanque de oxígeno mejorada! Nueva capacidad: " + this.tanqueOxigeno.getCapacidadMaxima());
            } else {
                System.out.println("No tienes suficientes recursos en la bodega de la nave para mejorar el tanque de oxígeno.");
                System.out.println("Recursos necesarios: " + plataNecesaria + " PLATA y " + cuarzoNecesario + " CUARZO.");
                System.out.println("Recursos disponibles: " + plataDisponible + " PLATA y " + cuarzoDisponible + " CUARZO.");
            }
        } else {
            System.out.println("Necesitas la mejora del tanque de oxígeno para poder mejorar su capacidad.");
        }
    }
    public void crearTrajeTermico(){
        // requiere 10*SILICIO 3*ORO y 5*CUARZO
        // extrae los recursos de la bodega de la naveExploradora
        if (!this.trajeTermico) {
            int silicioNecesario = 10;
            int oroNecesario = 3;
            int cuarzoNecesario = 5;
            int silicioDisponible = 0;
            int oroDisponible = 0;
            int cuarzoDisponible = 0;

            // Contar silicio, oro y cuarzo en la bodega de la nave
            for (Item item : this.getNave().getInventario()) {
                if (item.getTipo() == ItemTipo.SILICIO) {
                    silicioDisponible = item.getCantidad();
                } else if (item.getTipo() == ItemTipo.ORO) {
                    oroDisponible = item.getCantidad();
                } else if (item.getTipo() == ItemTipo.CUARZO) {
                    cuarzoDisponible = item.getCantidad();
                }
            }

            if (silicioDisponible >= silicioNecesario && oroDisponible >= oroNecesario && cuarzoDisponible >= cuarzoNecesario) {
                // Extraer los recursos necesarios
                this.getNave().transferirObjetos(ItemTipo.SILICIO, silicioNecesario, this.getNave().getInventario(), new ArrayList<>());
                this.getNave().transferirObjetos(ItemTipo.ORO, oroNecesario, this.getNave().getInventario(), new ArrayList<>());
                this.getNave().transferirObjetos(ItemTipo.CUARZO, cuarzoNecesario, this.getNave().getInventario(), new ArrayList<>());

                // Crear el traje térmico
                this.trajeTermico = true;
                System.out.println("¡Traje térmico creado! Ahora puedes acceder a zonas de alta temperatura.");
            } else {
                System.out.println("No tienes suficientes recursos en la bodega de la nave para crear el traje térmico.");
                System.out.println("Recursos necesarios: " + silicioNecesario + " SILICIO, " + oroNecesario + " ORO y " + cuarzoNecesario + " CUARZO.");
                System.out.println("Recursos disponibles: " + silicioDisponible + " SILICIO, " + oroDisponible + " ORO y " + cuarzoDisponible + " CUARZO.");
            }
        } else {
            System.out.println("Ya tienes un traje térmico.");
        }
    }
    public void instalarModuloProfundidad(){
        if (this.zonas.getNaveEstrellada().isModuloEncontrado()){
            NaveExploradora.ModuloProfundidad moduloProfundidad = this.getNave().new ModuloProfundidad();
            moduloProfundidad.aumentarProfundidad();
            System.out.println("¡Módulo de profundidad instalado! Nueva profundidad máxima soportada por la nave: " + this.getNave().getProfundidadSoportada() + " metros.");
        }
    }
    public void crearRobotExcavador(){}
    public void mejorarCargaRobot(){}
    public void repararRobot(){}
    public void repararNaveEstrellada(){
        // requiere PLANO_NAVE , 50*TITANIO , 30*ACERO , 15*URANIO y 20*SULFURO
        // extrae los recursos de la bodega de el jugador
        // activa el final del juego
        if (this.tienePlanos) {
            int titanioNecesario = 50;
            int aceroNecesario = 30;
            int uranioNecesario = 15;
            int sulfuroNecesario = 20;
            int titanioDisponible = 0;
            int aceroDisponible = 0;
            int uranioDisponible = 0;
            int sulfuroDisponible = 0;

            // Contar titanio, acero, uranio y sulfuro en la bodega de la nave
            for (Item item : this.getInventario()) {
                if (item.getTipo() == ItemTipo.TITANIO) {
                    titanioDisponible = item.getCantidad();
                } else if (item.getTipo() == ItemTipo.ACERO) {
                    aceroDisponible = item.getCantidad();
                } else if (item.getTipo() == ItemTipo.URANIO) {
                    uranioDisponible = item.getCantidad();
                } else if (item.getTipo() == ItemTipo.SULFURO) {
                    sulfuroDisponible = item.getCantidad();
                }
            }

            if (titanioDisponible >= titanioNecesario && aceroDisponible >= aceroNecesario && uranioDisponible >= uranioNecesario && sulfuroDisponible >= sulfuroNecesario) {
                // Extraer los recursos necesarios
                this.getNave().transferirObjetos(ItemTipo.TITANIO, titanioNecesario, this.getInventario(), new ArrayList<>());
                this.getNave().transferirObjetos(ItemTipo.ACERO, aceroNecesario, this.getInventario(), new ArrayList<>());
                this.getNave().transferirObjetos(ItemTipo.URANIO, uranioNecesario, this.getInventario(), new ArrayList<>());
                this.getNave().transferirObjetos(ItemTipo.SULFURO, sulfuroNecesario, this.getInventario(), new ArrayList<>());

                Main.finalDelJuego(); 
        } else {
                System.out.println("No tienes suficientes recursos en la bodega de la nave para reparar la nave estrellada.");
                System.out.println("Recursos necesarios: " + titanioNecesario + " TITANIO, " + aceroNecesario + " ACERO, " + uranioNecesario + " URANIO y " + sulfuroNecesario + " SULFURO.");
                System.out.println("Recursos disponibles: " + titanioDisponible + " TITANIO, " + aceroDisponible + " ACERO, " + uranioDisponible + " URANIO y " + sulfuroDisponible + " SULFURO.");
            }
        } else {
            System.out.println("Necesitas los planos de la nave para poder repararla.");
        }
    }

    
}
