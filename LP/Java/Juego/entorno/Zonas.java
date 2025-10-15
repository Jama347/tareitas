package Juego.entorno;

public class Zonas {

    private ZonaArrecife zonaArrecife;
    private ZonaProfunda zonaProfunda;  
    private ZonaVolcanica zonaVolcanica;
    private NaveEstrellada naveEstrellada;
    // crea cada una de las zonas
    public Zonas() {
        this.zonaArrecife = new ZonaArrecife
        ("Zona Arrecife", 1, 199);
        this.zonaProfunda = new ZonaProfunda
        ("Zona Profunda", 200, 999);
        this.zonaVolcanica = new ZonaVolcanica
        ("Zona Volcánica", 1000, 1500);
        this.naveEstrellada = new NaveEstrellada
        ("Nave Estrellada", 0, 0);
    }

    public ZonaArrecife getArrecife() {
        return zonaArrecife;
    }
    public ZonaProfunda getProfunda() {
        return zonaProfunda;
    }
    public ZonaVolcanica getVolcanica() {
        return zonaVolcanica;
    }
    public NaveEstrellada getNaveEstrellada() {
        return naveEstrellada;
    }

    public Zona getZonaPorProfundidad(int profundidad) {
        if (profundidad >= zonaArrecife.getProfundidadMin() && profundidad <= zonaArrecife.getProfundidadMax()) {
            return zonaArrecife;
        } else if (profundidad >= zonaProfunda.getProfundidadMin() && profundidad <= zonaProfunda.getProfundidadMax()) {
            return zonaProfunda;
        } else if (profundidad >= zonaVolcanica.getProfundidadMin() && profundidad <= zonaVolcanica.getProfundidadMax()) {
            return zonaVolcanica;
        } else {
            return null; // fuera de rango
        }
    }
}
