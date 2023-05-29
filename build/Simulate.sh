echo what particle would you like to use?
read particle

new="'s/particle gamma/particle "$particle"/g'"
old="'s/particle "$particle"/particle gamma /g'"

eval sed -i $new vis.mac

echo What is the energy of the particle in MeV?
read energy

new2="'s/energy 1234 MeV/energy "$energy" MeV/g'"
old2="'s/energy "$energy" MeV/energy 1234 MeV/g'"

eval sed -i $new2 vis.mac
./Rad_Demo > a.txt
eval sed -i $old vis.mac
eval sed -i $old2 vis.mac

root -l -q grade.C

