package Juego.objetos;

import Juego.player.Jugador;

public interface AccesoProfundidad {
    
    public boolean puedeAcceder(int profundidad);

    public void accederProfundidad(Jugador jugador, int nuevaProfundidad);
    //para subir o bajar, esta aqui porque tanto la nave como el jugador pueden subir y bajar :3
}
