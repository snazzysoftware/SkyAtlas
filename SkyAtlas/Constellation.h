//
//  Constellation.h
//  SkyAtlas
//
//  Created by Adam French on 02/03/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#ifndef __SkyAtlas__Constellation__
#define __SkyAtlas__Constellation__

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "Star.h"

namespace SkyAtlas
{
    enum ConstellationCode
    {
        NONE,
        Andromeda,
        Antlia,
        Apus,
        Aquarius,
        Aquila,
        Ara,
        Aries,
        Auriga,
        Bootes,
        Caelum,
        Camelopardalis,
        Cancer,
        CanesVenatici,
        CanisMajor,
        CanisMinor,
        Capricornus,
        Carina,
        Cassiopeia,
        Centaurus,
        Cepheus,
        Cetus,
        Chamaeleon,
        Circinus,
        Columba,
        ComaBerenices,
        CoronaAustralis,
        CoronaBorealis,
        Corvus,
        Crater,
        Crux,
        Cygnus,
        Delphinus,
        Dorado,
        Draco,
        Equuleus,
        Eridanus,
        Fornax,
        Gemini,
        Grus,
        Hercules,
        Horologium,
        Hydra,
        Hydrus,
        Indus,
        Lacerta,
        Leo,
        LeoMinor,
        Lepus,
        Libra,
        Lupus,
        Lynx,
        Lyra,
        Mensa,
        Microscopium,
        Monoceros,
        Musca,
        Norma,
        Octans,
        Ophiucus,
        Orion,
        Pavo,
        Pegasus,
        Perseus,
        Phoenix,
        Pictor,
        Pisces,
        PiscesAustrinus,
        Puppis,
        Pyxis,
        Reticulum,
        Sagitta,
        Sagittarius,
        Scorpius,
        Sculptor,
        Scutum,
        Serpens,
        Sextans,
        Taurus,
        Telescopium,
        Triangulum,
        TriangulumAustrale,
        Tucana,
        UrsaMajor,
        UrsaMinor,
        Vela,
        Virgo,
        Volans,
        Vulpecula
    };
    
    static const std::pair<ConstellationCode, std::string> ConstellationNames[] =
    {
        std::pair<ConstellationCode, std::string>(NONE, ""),
        std::pair<ConstellationCode, std::string>(Andromeda, "And"),
        std::pair<ConstellationCode, std::string>(Antlia, "Ant"),
        std::pair<ConstellationCode, std::string>(Apus, "Aps"),
        std::pair<ConstellationCode, std::string>(Aquarius, "Aqr"),
        std::pair<ConstellationCode, std::string>(Aquila, "Aql"),
        std::pair<ConstellationCode, std::string>(Ara, "Ara"),
        std::pair<ConstellationCode, std::string>(Aries, "Ari"),
        std::pair<ConstellationCode, std::string>(Auriga, "Aur"),
        std::pair<ConstellationCode, std::string>(Bootes, "Boo"),
        std::pair<ConstellationCode, std::string>(Caelum, "Cae"),
        std::pair<ConstellationCode, std::string>(Camelopardalis, "Cam"),
        std::pair<ConstellationCode, std::string>(Cancer, "Cnc"),
        std::pair<ConstellationCode, std::string>(CanesVenatici, "CVn"),
        std::pair<ConstellationCode, std::string>(CanisMajor, "CMa"),
        std::pair<ConstellationCode, std::string>(CanisMinor, "CMi"),
        std::pair<ConstellationCode, std::string>(Capricornus, "Cap"),
        std::pair<ConstellationCode, std::string>(Carina, "Car"),
        std::pair<ConstellationCode, std::string>(Cassiopeia, "Cas"),
        std::pair<ConstellationCode, std::string>(Centaurus, "Cen"),
        std::pair<ConstellationCode, std::string>(Cepheus, "Cep"),
        std::pair<ConstellationCode, std::string>(Cetus, "Cet"),
        std::pair<ConstellationCode, std::string>(Chamaeleon, "Cha"),
        std::pair<ConstellationCode, std::string>(Circinus, "Cir"),
        std::pair<ConstellationCode, std::string>(Columba, "Col"),
        std::pair<ConstellationCode, std::string>(ComaBerenices, "Com"),
        std::pair<ConstellationCode, std::string>(CoronaAustralis, "CrA"),
        std::pair<ConstellationCode, std::string>(CoronaBorealis, "CrB"),
        std::pair<ConstellationCode, std::string>(Corvus, "Crv"),
        std::pair<ConstellationCode, std::string>(Crater, "Crt"),
        std::pair<ConstellationCode, std::string>(Crux, "Cru"),
        std::pair<ConstellationCode, std::string>(Cygnus, "Cyg"),
        std::pair<ConstellationCode, std::string>(Delphinus, "Del"),
        std::pair<ConstellationCode, std::string>(Dorado, "Dor"),
        std::pair<ConstellationCode, std::string>(Draco, "Dra"),
        std::pair<ConstellationCode, std::string>(Equuleus, "Equ"),
        std::pair<ConstellationCode, std::string>(Eridanus, "Eri"),
        std::pair<ConstellationCode, std::string>(Fornax, "For"),
        std::pair<ConstellationCode, std::string>(Gemini, "Gem"),
        std::pair<ConstellationCode, std::string>(Grus, "Gru"),
        std::pair<ConstellationCode, std::string>(Hercules, "Her"),
        std::pair<ConstellationCode, std::string>(Horologium, "Hor"),
        std::pair<ConstellationCode, std::string>(Hydra, "Hya"),
        std::pair<ConstellationCode, std::string>(Hydrus, "Hyi"),
        std::pair<ConstellationCode, std::string>(Indus, "Ind"),
        std::pair<ConstellationCode, std::string>(Lacerta, "Lac"),
        std::pair<ConstellationCode, std::string>(Leo, "Leo"),
        std::pair<ConstellationCode, std::string>(LeoMinor, "LMi"),
        std::pair<ConstellationCode, std::string>(Lepus, "Lep"),
        std::pair<ConstellationCode, std::string>(Libra, "Lib"),
        std::pair<ConstellationCode, std::string>(Lupus, "Lup"),
        std::pair<ConstellationCode, std::string>(Lynx, "Lyn"),
        std::pair<ConstellationCode, std::string>(Lyra, "Lyr"),
        std::pair<ConstellationCode, std::string>(Mensa, "Men"),
        std::pair<ConstellationCode, std::string>(Microscopium, "Mic"),
        std::pair<ConstellationCode, std::string>(Monoceros, "Mon"),
        std::pair<ConstellationCode, std::string>(Musca, "Mus"),
        std::pair<ConstellationCode, std::string>(Norma, "Nor"),
        std::pair<ConstellationCode, std::string>(Octans, "Oct"),
        std::pair<ConstellationCode, std::string>(Ophiucus, "Oph"),
        std::pair<ConstellationCode, std::string>(Orion, "Ori"),
        std::pair<ConstellationCode, std::string>(Pavo, "Pav"),
        std::pair<ConstellationCode, std::string>(Pegasus, "Peg"),
        std::pair<ConstellationCode, std::string>(Perseus, "Per"),
        std::pair<ConstellationCode, std::string>(Phoenix, "Phe"),
        std::pair<ConstellationCode, std::string>(Pictor, "Pic"),
        std::pair<ConstellationCode, std::string>(Pisces, "Psc"),
        std::pair<ConstellationCode, std::string>(PiscesAustrinus, "PsA"),
        std::pair<ConstellationCode, std::string>(Puppis, "Pup"),
        std::pair<ConstellationCode, std::string>(Pyxis, "Pyx"),
        std::pair<ConstellationCode, std::string>(Reticulum, "Ret"),
        std::pair<ConstellationCode, std::string>(Sagitta, "Sge"),
        std::pair<ConstellationCode, std::string>(Sagittarius, "Sgr"),
        std::pair<ConstellationCode, std::string>(Scorpius, "Sco"),
        std::pair<ConstellationCode, std::string>(Sculptor, "Scl"),
        std::pair<ConstellationCode, std::string>(Scutum, "Sct"),
        std::pair<ConstellationCode, std::string>(Serpens, "Ser"),
        std::pair<ConstellationCode, std::string>(Sextans, "Sex"),
        std::pair<ConstellationCode, std::string>(Taurus, "Tau"),
        std::pair<ConstellationCode, std::string>(Telescopium, "Tel"),
        std::pair<ConstellationCode, std::string>(Triangulum, "Tri"),
        std::pair<ConstellationCode, std::string>(TriangulumAustrale, "TrA"),
        std::pair<ConstellationCode, std::string>(Tucana, "Tuc"),
        std::pair<ConstellationCode, std::string>(UrsaMajor, "UMa"),
        std::pair<ConstellationCode, std::string>(UrsaMinor, "UMi"),
        std::pair<ConstellationCode, std::string>(Vela, "Vel"),
        std::pair<ConstellationCode, std::string>(Virgo, "Vir"),
        std::pair<ConstellationCode, std::string>(Volans, "Vol"),
        std::pair<ConstellationCode, std::string>(Vulpecula, "Vul")
    };
    
    class ConstellationLine
    {
    public:
        std::vector<Star> line;
        
        // Create a ConstellationLine from an input stream
        ConstellationLine(std::istream &input);
        
    };
    
    class Constellation
    {
    public:
        std::vector<ConstellationLine> lines;
        ConstellationCode code;
        
        // Create a Constellation from an input stream
        Constellation(std::istream &input);
        
    };

}

#endif /* defined(__SkyAtlas__Constellation__) */
