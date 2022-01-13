#! /usr/bin/env bash

set -e


# OoT

## Functions and variables
wget "https://docs.google.com/spreadsheets/d/17yPD3DqqH5lZeR7c_QmJfgxWgVyYkGgTLZoKcvLTwtw/export?format=csv&gid=1299953822" -O - | tr -d '\r' > "oot/tables/functions.csv"
wget "https://docs.google.com/spreadsheets/d/17yPD3DqqH5lZeR7c_QmJfgxWgVyYkGgTLZoKcvLTwtw/export?format=csv&gid=196803778"  -O - | tr -d '\r' > "oot/tables/variables.csv"

## boot
# wget "https://docs.google.com/spreadsheets/d/17yPD3DqqH5lZeR7c_QmJfgxWgVyYkGgTLZoKcvLTwtw/export?format=csv&gid=10092675"   -O - | tr -d '\r' > "oot/tables/boot.text.csv"

## code
# wget "https://docs.google.com/spreadsheets/d/17yPD3DqqH5lZeR7c_QmJfgxWgVyYkGgTLZoKcvLTwtw/export?format=csv&gid=204902945"  -O - | tr -d '\r' > "oot/tables/code.text.csv"

## n64dd
wget "https://docs.google.com/spreadsheets/d/17yPD3DqqH5lZeR7c_QmJfgxWgVyYkGgTLZoKcvLTwtw/export?format=csv&gid=959352547"  -O - | tr -d '\r' > "oot/tables/n64dd.text.csv"
wget "https://docs.google.com/spreadsheets/d/17yPD3DqqH5lZeR7c_QmJfgxWgVyYkGgTLZoKcvLTwtw/export?format=csv&gid=1208054228" -O - | tr -d '\r' > "oot/tables/n64dd.data.csv"
wget "https://docs.google.com/spreadsheets/d/17yPD3DqqH5lZeR7c_QmJfgxWgVyYkGgTLZoKcvLTwtw/export?format=csv&gid=2035868832" -O - | tr -d '\r' > "oot/tables/n64dd.rodata.csv"
wget "https://docs.google.com/spreadsheets/d/17yPD3DqqH5lZeR7c_QmJfgxWgVyYkGgTLZoKcvLTwtw/export?format=csv&gid=1720384253" -O - | tr -d '\r' > "oot/tables/n64dd.bss.csv"


# MM

## Functions and variables
# wget "https://docs.google.com/spreadsheets/d/12cKSs6fX211H_ufGUUSIjdPmlMbt3ZLyW71GLpAm0_4/export?format=csv&gid=1063621067" -O - | tr -d '\r' > "mm/tables/functions.csv"
# wget "https://docs.google.com/spreadsheets/d/12cKSs6fX211H_ufGUUSIjdPmlMbt3ZLyW71GLpAm0_4/export?format=csv&gid=1570476402" -O - | tr -d '\r' > "mm/tables/variables.csv"

## boot
# wget "https://docs.google.com/spreadsheets/d/12cKSs6fX211H_ufGUUSIjdPmlMbt3ZLyW71GLpAm0_4/export?format=csv&gid=269020656"  -O - | tr -d '\r' > "mm/tables/boot.text.csv"
# wget "https://docs.google.com/spreadsheets/d/12cKSs6fX211H_ufGUUSIjdPmlMbt3ZLyW71GLpAm0_4/export?format=csv&gid=680636738"  -O - | tr -d '\r' > "mm/tables/boot.data.csv"
# wget "https://docs.google.com/spreadsheets/d/12cKSs6fX211H_ufGUUSIjdPmlMbt3ZLyW71GLpAm0_4/export?format=csv&gid=1260565170" -O - | tr -d '\r' > "mm/tables/boot.rodata.csv"
# wget "https://docs.google.com/spreadsheets/d/12cKSs6fX211H_ufGUUSIjdPmlMbt3ZLyW71GLpAm0_4/export?format=csv&gid=1589823056" -O - | tr -d '\r' > "mm/tables/boot.bss.csv"

## code
# wget "https://docs.google.com/spreadsheets/d/12cKSs6fX211H_ufGUUSIjdPmlMbt3ZLyW71GLpAm0_4/export?format=csv&gid=0"          -O - | tr -d '\r' > "mm/tables/code.text.csv"
# wget "https://docs.google.com/spreadsheets/d/12cKSs6fX211H_ufGUUSIjdPmlMbt3ZLyW71GLpAm0_4/export?format=csv&gid=1298997316" -O - | tr -d '\r' > "mm/tables/code.data.csv"
# wget "https://docs.google.com/spreadsheets/d/12cKSs6fX211H_ufGUUSIjdPmlMbt3ZLyW71GLpAm0_4/export?format=csv&gid=1712837674" -O - | tr -d '\r' > "mm/tables/code.rodata.csv"
# wget "https://docs.google.com/spreadsheets/d/12cKSs6fX211H_ufGUUSIjdPmlMbt3ZLyW71GLpAm0_4/export?format=csv&gid=1266090971" -O - | tr -d '\r' > "mm/tables/code.bss.csv"
