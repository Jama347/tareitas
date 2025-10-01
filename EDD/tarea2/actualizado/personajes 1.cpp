/////
 // enemigos, armas y personajes del jueguito
 // - enemigos base
 // - enemigos resistentes
 // - enemigos fuertes
 // 
 // -armas melee
 // -armas melee + elementales
 // -armas ranger
 // -armas ranger + elemntales
 // -armas magicas low cost
 // -armas magicas high damage
 // 
 // -Personajes
 //
 ///

/// ===== ENEMIGOS BASE ===== ///
/////
 // desechos vivientes: 
 //      name=desecho_verde
 //      baseHealth=12
 //      Attack=10
 //      Defence.physic=0
 //      Defence.fire=0
 //      Defence.ice=0
 //      Defence.wind=0
 //      Defence.electric=0
 //      accuracy=0.85
 // 
 //      name=desecho_azul
 //      baseHealth=14
 //      Attack=8
 //      Defence.physic=0.01
 //      Defence.fire=-0.1
 //      Defence.ice=0.1
 //      Defence.wind=0.1
 //      Defence.electric=-0.1
 //      accuracy=0.85
 // 
 //      name=desecho_rojo
 //      baseHealth=10
 //      Attack=12
 //      Defence.physic=0.01
 //      Defence.fire=0.01
 //      Defence.ice=-0.1
 //      Defence.wind=-0.1
 //      Defence.electric=0.01
 //      accuracy=0.85
 // 
 // cadaveres en descompasicion: 
 //      name=no_muerto
 //      baseHealth=18
 //      Attack=12
 //      Defence.physic=0
 //      Defence.fire=0.04
 //      Defence.ice=0.04
 //      Defence.wind=-0.3
 //      Defence.electric=-0.3
 //      accuracy=0.8
 // 
 //      name=no_muerto_pesado
 //      baseHealth=20
 //      Attack=12
 //      Defence.physic=0.5
 //      Defence.fire=0
 //      Defence.ice=0
 //      Defence.wind=-0.2
 //      Defence.electric=-0.2
 //      accuracy=0.8
 // 
 //      name=no_muerto_violento
 //      baseHealth=14
 //      Attack=16
 //      Defence.physic=0
 //      Defence.fire=0.04
 //      Defence.ice=0.04
 //      Defence.wind=-0.2
 //      Defence.electric=-0.2
 //      accuracy=0.85
 ///

 /// ===== ENEMIGOS RESISTENTES ===== ///
 /////
  // Rocas Vivientes:
  //     name=Gran_Roca
 //      baseHealth=35
 //      Attack=4
 //      Defence.physic=-0.5
 //      Defence.fire=0.5
 //      Defence.ice=0.5
 //      Defence.wind=0.5
 //      Defence.electric=0.5
 //      accuracy=0.6
  // 
  //     name=Roca_Brillante_Caliente
 //      baseHealth=30
 //      Attack=6
 //      Defence.physic=-0.5
 //      Defence.fire=0.9
 //      Defence.ice=0.2
 //      Defence.wind=0.2
 //      Defence.electric=0.2
 //      accuracy=0.6
 // 
 //      name=Roca_Brillante_Fria
 //      baseHealth=37
 //      Attack=3
 //      Defence.physic=-0.6
 //      Defence.fire=-0.3
 //      Defence.ice=0.95
 //      Defence.wind=0.4
 //      Defence.electric=0.4
 //      accuracy=0.5
 // 
 //      name=Roca_Flotante
 //      baseHealth=33
 //      Attack=9
 //      Defence.physic=-0.4
 //      Defence.fire=0.6
 //      Defence.ice=-0.2
 //      Defence.wind=1
 //      Defence.electric=-0.4
 //      accuracy=0.75
 // 
 //      name=Roca_Eliectrica
 //      baseHealth=35
 //      Attack=7
 //      Defence.physic=-0.5
 //      Defence.fire=0.2
 //      Defence.ice=0.2
 //      Defence.wind=0.2
 //      Defence.electric=0.9
 //      accuracy=0.85
 // 
 // Ratas: (se alimentan de desechos magicos)
 //      name=Rata
 //      baseHealth=17
 //      Attack=10
 //      Defence.physic=-1
 //      Defence.fire=0.8
 //      Defence.ice=0.8
 //      Defence.wind=0.8
 //      Defence.electric=0.8
 //      accuracy=0.8
 // 
 //      name=Rata_Bola_de_Fuego
 //      baseHealth=17
 //      Attack=10
 //      Defence.physic=-1
 //      Defence.fire=-1
 //      Defence.ice=0.95
 //      Defence.wind=0.95
 //      Defence.electric=0.95
 //      accuracy=0.8
 // 
 //      name=Rata_Carambano
 //      baseHealth=17
 //      Attack=10
 //      Defence.physic=-1
 //      Defence.fire=0.95
 //      Defence.ice=-1
 //      Defence.wind=0.95
 //      Defence.electric=0.95
 //      accuracy=0.8
 // 
 //      name=Rata_Vendaval
 //      baseHealth=17
 //      Attack=10
 //      Defence.physic=-1
 //      Defence.fire=0.95
 //      Defence.ice=0.95
 //      Defence.wind=-1
 //      Defence.electric=0.95
 //      accuracy=0.8
 // 
 //      name=Rata_Carga
 //      baseHealth=17
 //      Attack=10
 //      Defence.physic=-1
 //      Defence.fire=0.95
 //      Defence.ice=0.95
 //      Defence.wind=0.95
 //      Defence.electric=-1
 //      accuracy=0.8
  ///
 
 /// ===== ENEMIGOS FUERTES ===== ///
 /////
  // saqueadores: (expertos en tecnologia)
  //     name=Saqueador
 //      baseHealth=10
 //      Attack=16
 //      Defence.physic=0.2
 //      Defence.fire=-0.1
 //      Defence.ice=-0.1
 //      Defence.wind=-0.1
 //      Defence.electric=-0.1
 //      accuracy=0.65
 // 
 //      name=Saqueador_con_kunai
 //      baseHealth=12
 //      Attack=20
 //      Defence.physic=0
 //      Defence.fire=0.1
 //      Defence.ice=0.1
 //      Defence.wind=-0.3
 //      Defence.electric=-0.1
 //      accuracy=0.70
 // 
 //      name=Saqueador_sobre_una_ballesta
 //      baseHealth=14
 //      Attack=30
 //      Defence.physic=0.2
 //      Defence.fire=-0-2
 //      Defence.ice=-0.2
 //      Defence.wind=-0.1
 //      Defence.electric=0.3
 //      accuracy=0.3
 // 
 //      name=Saqueador_Brayan
 //      baseHealth=6
 //      Attack=19
 //      Defence.physic=0.2
 //      Defence.fire=-0.3
 //      Defence.ice=0.1
 //      Defence.wind=-0.1
 //      Defence.electric=0
 //      accuracy=0.85
 // 
 //      name=Saqueador_en_un_tanque_roto
 //      baseHealth=24
 //      Attack=35
 //      Defence.physic=0.6
 //      Defence.fire=-0.2
 //      Defence.ice=-0.2
 //      Defence.wind=-0.2
 //      Defence.electric=-0.2
 //      accuracy=0.45
 // 
 //      name=Saqueador_en_un_cohete
 //      baseHealth=4
 //      Attack=35
 //      Defence.physic=0
 //      Defence.fire=0
 //      Defence.ice=0
 //      Defence.wind=0
 //      Defence.electric=0
 //      accuracy=0.50
 // 
 // Mutantes: (muy violentos pero casi mas tontos)
 //      name=Mutante
 //      baseHealth=18
 //      Attack=19
 //      Defence.physic=0.2
 //      Defence.fire=-0.1
 //      Defence.ice=0.2
 //      Defence.wind=-0.3
 //      Defence.electric=0.1
 //      accuracy=0.3
 // 
 //      name=Mutante_con_un_palo
 //      baseHealth=18
 //      Attack=24
 //      Defence.physic=0
 //      Defence.fire=-0.4
 //      Defence.ice=0
 //      Defence.wind=0
 //      Defence.electric=0.3
 //      accuracy=0.2
 // 
 //      name=Orco_con_dos_palos
 //      baseHealth=18
 //      Attack=29
 //      Defence.physic=0
 //      Defence.fire=-0.8
 //      Defence.ice=-0.4
 //      Defence.wind=0
 //      Defence.electric=0.6
 //      accuracy=0.15
 // 
 //      name=Dos_Metantes_amarrados_por_la_lengua
 //      baseHealth=36
 //      Attack=38
 //      Defence.physic=0
 //      Defence.fire=0
 //      Defence.ice=0
 //      Defence.wind=0
 //      Defence.electric=0
 //      accuracy=0.1
 // 
 //      name=Mutante_Mujer
 //      baseHealth=16
 //      Attack=18
 //      Defence.physic=-0.3
 //      Defence.fire=0
 //      Defence.ice=-0.1
 //      Defence.wind=0
 //      Defence.electric=0.2
 //      accuracy=0.6
 // 
 // Enemigos especiales: (me la estoy pasando muy bien)
 //      name=Pois
 //      baseHealth=150
 //      Attack=0.5
 //      Defence.physic=0.85
 //      Defence.fire=0.85
 //      Defence.ice=0.85
 //      Defence.wind=0.85
 //      Defence.electric=0.85
 //      accuracy=0.95
 // 
 //      name=Jama
 //      baseHealth=0.001
 //      Attack=999
 //      Defence.physic=-1
 //      Defence.fire=-1
 //      Defence.ice=-1
 //      Defence.wind=-1
 //      Defence.electric=-1
 //      accuracy=0.0001     
  ///


  /// ===== ARMAS ===== ///

  /// ===== ARMAS MELEE ===== ///
  /////
   //        name=kunai
   //        accuracy=1
   //        attack.physic=5
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=5
   //        type=1
   //        burst=1
   //        multipleShot=false
   // 
   //        name=kunaikunai
   //        accuracy=1
   //        attack.physic=10
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=10
   //        type=1
   //        burst=2
   //        multipleShot=false
   // 
   //        name=Machete
   //        accuracy=1
   //        attack.physic=8
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=7
   //        type=1
   //        burst=1
   //        multipleShot=false
   // 
   //        name=Machete_al_Machote
   //        accuracy=1
   //        attack.physic=13
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=9
   //        type=1
   //        burst=1
   //        multipleShot=false
   // 
   //        name=Hacha_Oxidada
   //        accuracy=0.9
   //        attack.physic=9
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=7
   //        type=1
   //        burst=1
   //        multipleShot=false
   // 
   //        name=Hacha
   //        accuracy=0.9
   //        attack.physic=15
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=10
   //        type=1
   //        burst=1
   //        multipleShot=false
   // 
   //        name=Hacha_de_Guerra
   //        accuracy=0.85
   //        attack.physic=20
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=15
   //        type=1
   //        burst=2
   //        multipleShot=false
   // 
   //        name=Microfono
   //        accuracy=1
   //        attack.physic=6
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=4
   //        type=1
   //        burst=1
   //        multipleShot=false
   // 
   //        name=Chatarra
   //        accuracy=0.7
   //        attack.physic=2
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=7
   //        type=1
   //        burst=1
   //        multipleShot=false
   // 
   //        name=TUS_MANOS!!!
   //        accuracy=1
   //        attack.physic=3
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=2
   //        type=1
   //        burst=5
   //        multipleShot=false
   // 
   //        name=Puños_Americano
   //        accuracy=1
   //        attack.physic=5
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=2
   //        type=1
   //        burst=5
   //        multipleShot=false
   // 
   //        name=Latigo_de_Cuero
   //        accuracy=0.9
   //        attack.physic=10
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=12
   //        type=1
   //        burst=1
   //        multipleShot=true
   // 
   //        name=Cadena_Larga
   //        accuracy=0.9
   //        attack.physic=15
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=17
   //        type=1
   //        burst=1
   //        multipleShot=true
   ///
/// ===== ARMAS MELEE + ELEMENTALES ===== ///
/////
 //          name=Kunais_Cargados
   //        accuracy=1
   //        attack.physic=10
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=5
   //        energyCost=10
   //        type=1
   //        burst=2
   //        multipleShot=false
   // 
   //        name=Machete_en_Llamas
   //        accuracy=1
   //        attack.physic=13
   //        attack.fire=7
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=9
   //        type=1
   //        burst=1
   //        multipleShot=false
   // 
   //        name=Hacha_Tundrica
   //        accuracy=0.85
   //        attack.physic=20
   //        attack.fire=0
   //        attack.ice=10
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=15
   //        type=1
   //        burst=2
   //        multipleShot=false
   // 
   //        name=Chatarra_Radioactiva
   //        accuracy=0.85
   //        attack.physic=2
   //        attack.fire=2
   //        attack.ice=2
   //        attack.wind=2
   //        attack.electric=2
   //        energyCost=7
   //        type=1
   //        burst=1
   //        multipleShot=false    
   // 
   //        name=Puños_ligeros
   //        accuracy=1
   //        attack.physic=5
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=3
   //        attack.electric=0
   //        energyCost=10
   //        type=1
   //        burst=5
   //        multipleShot=false
 ///
/// ===== ARMAS RANGER ===== ///
/////
 //          name=Arco_Improvisado
   //        accuracy=0.7
   //        attack.physic=9
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=4
   //        type=2
   //        burst=5
   //        multipleShot=false
   //        baseAmmo=5
   //        reloadCost=15
   //        
   //        name=Arco
   //        accuracy=0.9
   //        attack.physic=12
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=10
   //        type=2
   //        burst=3
   //        multipleShot=false
   //        baseAmmo=6
   //        reloadCost=15
   // 
   //        name=Ballesta
   //        accuracy=0.8
   //        attack.physic=16
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=10
   //        type=2
   //        burst=2
   //        multipleShot=false
   //        baseAmmo=3
   //        reloadCost=17
   // 
   //        name=Pistola
   //        accuracy=0.95
   //        attack.physic=1
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=3
   //        type=2
   //        burst=10
   //        multipleShot=false
   //        baseAmmo=30
   //        reloadCost=17
   // 
   //        name=Escopeta
   //        accuracy=0.8
   //        attack.physic=18
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=14
   //        type=2
   //        burst=2
   //        multipleShot=true
   //        baseAmmo=4
   //        reloadCost=19
   // 
   //        name=ESCOPETA!!!
   //        accuracy=0.85
   //        attack.physic=25
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=18
   //        type=2
   //        burst=2
   //        multipleShot=true
   //        baseAmmo=4
   //        reloadCost=25
   // 
   //        name=smg
   //        accuracy=0.95
   //        attack.physic=0.5
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=7
   //        type=2
   //        burst=30
   //        multipleShot=false
   //        baseAmmo=60
   //        reloadCost=17
   // 
   //        name=RATATATATTATATTATATATTA!!!!!
   //        accuracy=0.95
   //        attack.physic=1
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=7
   //        type=2
   //        burst=30
   //        multipleShot=false
   //        baseAmmo=60
   //        reloadCost=17
   // 
   //        name=BOOM!!!
   //        accuracy=0.3
   //        attack.physic=30
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=30
   //        type=2
   //        burst=1
   //        multipleShot=true
   //        baseAmmo=5
   //        reloadCost=30
   // 
   //        name=KABOOM!!!
   //        accuracy=0.3
   //        attack.physic=50
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=35
   //        type=2
   //        burst=1
   //        multipleShot=true
   //        baseAmmo=5
   //        reloadCost=30      
 ///
/// ===== ARMAS RANGER + ELEMENTALES===== ///
/////
 //          name=Ballesta_Encantada
   //        accuracy=0.8
   //        attack.physic=16
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=4
   //        attack.electric=4
   //        energyCost=10
   //        type=2
   //        burst=2
   //        multipleShot=false
   //        baseAmmo=5
   //        reloadCost=15
   // 
   //        name=Lanzallamas
   //        accuracy=0.95
   //        attack.physic=2
   //        attack.fire=20
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=20
   //        type=2
   //        burst=5
   //        multipleShot=true
   //        baseAmmo=30
   //        reloadCost=7
 ///
/// ===== ARMAS MAGICAS LOW COST===== ///
/////
 //          name=Ascuas
   //        accuracy=0.95
   //        attack.physic=0
   //        attack.fire=13
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=5
   //        type=3
   //        burst=3
   //        multipleShot=true
   //        manaCost=5
   //        physicMagic=3 
   // 
   //        name=Bola_Hielo
   //        accuracy=0.95
   //        attack.physic=0
   //        attack.fire=0
   //        attack.ice=15
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=5
   //        type=3
   //        burst=3
   //        multipleShot=false
   //        manaCost=5
   //        physicMagic=3    
   // 
   //        name=Aerochorro
   //        accuracy=0.95
   //        attack.physic=0
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=13
   //        attack.electric=0
   //        energyCost=5
   //        type=3
   //        burst=3
   //        multipleShot=true
   //        manaCost=5
   //        physicMagic=3 
   // 
   //        name=Chispa
   //        accuracy=0.95
   //        attack.physic=0
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=15
   //        energyCost=5
   //        type=3
   //        burst=3
   //        multipleShot=false
   //        manaCost=5
   //        physicMagic=3
   // 
   //        name=Ascuas_Aerochorreantes
   //        accuracy=0.95
   //        attack.physic=0
   //        attack.fire=13
   //        attack.ice=0
   //        attack.wind=13
   //        attack.electric=0
   //        energyCost=10
   //        type=3
   //        burst=6
   //        multipleShot=true
   //        manaCost=10
   //        physicMagic=3
   // 
   //        name=Bola_de_ChispaHielo
   //        accuracy=0.95
   //        attack.physic=0
   //        attack.fire=0
   //        attack.ice=15
   //        attack.wind=0
   //        attack.electric=15
   //        energyCost=10
   //        type=3
   //        burst=6
   //        multipleShot=false
   //        manaCost=10
   //        physicMagic=3
   // 
   //        name=TetraElementalidad
   //        accuracy=0.95
   //        attack.physic=0
   //        attack.fire=7
   //        attack.ice=7
   //        attack.wind=7
   //        attack.electric=7
   //        energyCost=10
   //        type=3
   //        burst=5
   //        multipleShot=true
   //        manaCost=10
   //        physicMagic=3
   // 
 ///
/// ===== ARMAS MAGICAS HIGH DAMAGE===== ///
/////
 //          name=Bola_de_Fuego
   //        accuracy=0.9
   //        attack.physic=0
   //        attack.fire=22
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=7
   //        type=3
   //        burst=3
   //        multipleShot=true
   //        manaCost=20
   //        physicMagic=10
   // 
   //        name=Carambano
   //        accuracy=0.9
   //        attack.physic=0
   //        attack.fire=0
   //        attack.ice=27
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=7
   //        type=3
   //        burst=3
   //        multipleShot=false
   //        manaCost=20
   //        physicMagic=10
   // 
   //        name=Vendaval
   //        accuracy=0.9
   //        attack.physic=0
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=22
   //        attack.electric=0
   //        energyCost=7
   //        type=3
   //        burst=3
   //        multipleShot=true
   //        manaCost=20
   //        physicMagic=10
   // 
   //        name=Chispa
   //        accuracy=0.9
   //        attack.physic=0
   //        attack.fire=0
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=27
   //        energyCost=7
   //        type=3
   //        burst=3
   //        multipleShot=false
   //        manaCost=20
   //        physicMagic=10
   // 
   //        name=Vendaval_de_Fuego
   //        accuracy=0.9
   //        attack.physic=0
   //        attack.fire=22
   //        attack.ice=0
   //        attack.wind=22
   //        attack.electric=0
   //        energyCost=10
   //        type=3
   //        burst=4
   //        multipleShot=true
   //        manaCost=25
   //        physicMagic=14
   // 
   //        name=Carambano_Chispiante
   //        accuracy=0.9
   //        attack.physic=0
   //        attack.fire=0
   //        attack.ice=27
   //        attack.wind=0
   //        attack.electric=27
   //        energyCost=10
   //        type=3
   //        burst=5
   //        multipleShot=false
   //        manaCost=25
   //        physicMagic=14
   // 
   //        name=Hiper_TetraElementalidad
   //        accuracy=0.9
   //        attack.physic=0
   //        attack.fire=11
   //        attack.ice=14
   //        attack.wind=11
   //        attack.electric=14
   //        energyCost=15
   //        type=3
   //        burst=2
   //        multipleShot=true
   //        manaCost=35
   //        physicMagic=15
   // 
   //        name=ZETTAFLAREEEEEE!!!!
   //        accuracy=0.5
   //        attack.physic=0
   //        attack.fire=999
   //        attack.ice=0
   //        attack.wind=0
   //        attack.electric=0
   //        energyCost=50
   //        type=3
   //        burst=1
   //        multipleShot=true
   //        manaCost=50
   //        physicMagic=3
 ///
/// ===== PERSONAJES===== ///
/////
 //      name=Guapo_Rubio_Mazado
 //      baseHealth=120
 //      baseEnergy=30
 //      baseMana=10
 //      manaGain=3
 //      accuracy=0.95 
 //      Winventory[0]=Machete
 //      invLenght=3
 //      Attack.physic=10
 //      Attack.fire=0
 //      Attack.ice=0
 //      Attack.wind=0
 //      Attack.electric=0
 // 
 //      name=Japones_Vestido_de_Ninja
 //      baseHealth=100
 //      baseEnergy=25
 //      baseMana=20
 //      manaGain=5
 //      accuracy=0.99 
 //      Winventory[0]=kunai
 //      invLenght=2
 //      Attack.physic=10
 //      Attack.fire=5
 //      Attack.ice=5
 //      Attack.wind=5
 //      Attack.electric=5
 // 
 //      name=Swiftie
 //      baseHealth=90
 //      baseEnergy=40
 //      baseMana=10
 //      manaGain=3
 //      accuracy=0.9 
 //      Winventory[0]=Arco_Improvisado
 //      invLenght=5
 //      Attack.physic=10
 //      Attack.fire=0
 //      Attack.ice=0
 //      Attack.wind=0
 //      Attack.electric=0
 // 
 //      name=Freddy_Mercury
 //      baseHealth=110
 //      baseEnergy=35
 //      baseMana=10
 //      manaGain=4
 //      accuracy=0.95 
 //      Winventory[0]=Microfono
 //      invLenght=3
 //      Attack.physic=9
 //      Attack.fire=2
 //      Attack.ice=0
 //      Attack.wind=2
 //      Attack.electric=0
 // 
 //      name=Rata_Mutante
 //      baseHealth=70
 //      baseEnergy=40
 //      baseMana=30
 //      manaGain=15
 //      accuracy=0.8 
 //      Winventory[0]=Chatarra
 //      invLenght=1
 //      Attack.physic=3
 //      Attack.fire=10
 //      Attack.ice=10
 //      Attack.wind=10
 //      Attack.electric=10
 // 
 //      name=Cientifico_del_Tzar
 //      baseHealth=85
 //      baseEnergy=25
 //      baseMana=35
 //      manaGain=12
 //      accuracy=0.95 
 //      Winventory[0]=Ascuas
 //      invLenght=6
 //      Attack.physic=2
 //      Attack.fire=15
 //      Attack.ice=7
 //      Attack.wind=15
 //      Attack.electric=7
 // 
 //      name=Espia_de_la_CIA
 //      baseHealth=105
 //      baseEnergy=27
 //      baseMana=32
 //      manaGain=12
 //      accuracy=0.95 
 //      Winventory[0]=Bola_Hielo
 //      invLenght=5
 //      Attack.physic=4
 //      Attack.fire=5
 //      Attack.ice=17
 //      Attack.wind=5
 //      Attack.electric=17
 // 
 //      name=Persona_con_Mochila
 //      baseHealth=115
 //      baseEnergy=35
 //      baseMana=10
 //      manaGain=4
 //      accuracy=0.9 
 //      Winventory[0]=Hacha_Oxidada
 //      invLenght=10
 //      Attack.physic=10
 //      Attack.fire=0
 //      Attack.ice=0
 //      Attack.wind=0
 //      Attack.electric=0

