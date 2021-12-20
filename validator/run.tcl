
### default setting
set Project     Validator
set Solution    SolutionX
set Device      "xcvu3p-ffvc1517-3-e"
set Flow        ""
set Clock       8
set DefaultFlag 1

#### main part

# Project settings
open_project $Project -reset

# Add the file for synthesis
add_files validator.c
#add_files src/rs_roms.c

# Add testbench files for co-simulation
add_files -tb  validator_test.c

# Set top module of the design
set_top validator

# Solution settings
open_solution -reset $Solution

# Add library
set_part $Device

# Set the target clock period
create_clock -period $Clock
set_clock_uncertainty 0.3ns

# csim_design

#############
# SYNTHESIS #
#############
#config_schedule -verbose
csynth_design

#################
# CO-SIMULATION #
#################
#cosim_design -tool modelsim -rtl verilog -trace_level all
# cosim_design -rtl verilog -trace_level all

# ##################
# # IMPLEMENTATION #
# ##################
# export_design -evaluate verilog -format ipxact


exit
