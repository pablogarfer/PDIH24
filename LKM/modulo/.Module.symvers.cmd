cmd_/home/pablogarfer/Documents/modulo/Module.symvers := sed 's/\.ko$$/\.o/' /home/pablogarfer/Documents/modulo/modules.order | scripts/mod/modpost -m -a  -o /home/pablogarfer/Documents/modulo/Module.symvers -e -i Module.symvers   -T -
