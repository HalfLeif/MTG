#pragma once

#include "../core/library.h"

inline Library kTHB = Library::Builder()
                          .SetLimited()
                          .AddSpell(MakeSpell("G", 1, "MossViper"))
                          .AddSpell(MakeSpell("G", 1, "Spider"))

                          .AddSpell(MakeSpell("WG", 1, "BronzehideLion"))
                          .AddSpell(MakeSpell("1G", 1, "Beetle"))
                          .AddSpell(MakeSpell("1G", 0, "Warbriar"))
                          .AddSpell(MakeSpell("1W", 0, "IndomitableWill"))

                          .AddSpell(MakeSpell("2W", 1, "FavoredOfIroas"))
                          .AddSpell(MakeSpell("2G", 1, "NyxHerald"))
                          .AddSpell(MakeSpell("2G", 1, "Champion"))
                          .AddSpell(MakeSpell("2W", 0, "DreadfulApathy"))
                          .AddSpell(MakeSpell("2W", 0, "BanishingLight"))
                          .AddSpell(MakeSpell("3", 0, "EntrancingLyre"))

                          .AddSpell(MakeSpell("3W", 1, "Pegasus"))
                          .AddSpell(MakeSpell("2GG", 1, "Typhon"))
                          .AddSpell(MakeSpell("2GG", 1, "Typhon"))
                          .AddSpell(MakeSpell("2GG", 5, "Renata"))
                          .AddSpell(MakeSpell("3G", 0, "Mantle"))
                          .AddSpell(MakeSpell("3W", 0, "TriumphantSurge"))
                          .AddSpell(MakeSpell("2WW", 0, "Intervention"))

                          .AddSpell(MakeSpell("4G", 1, "Forerunner"))
                          .AddSpell(MakeSpell("4GG", 1, "Pheres"))
                          .AddSpell(MakeSpell("3GGG", 1, "Colossus"))
                          .AddSpell(MakeSpell("3WW", 0, "Elspeth"))

                          .AddLand(Shore(), Experiment::exp)
                          .Build();
