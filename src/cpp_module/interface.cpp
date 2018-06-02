#include "vpi_user.h"
#include "processor.h"

processor proc;

static int processor_load(char*user_data)
{
   vpiHandle systf_handle, arg_iterator, arg_handle;
   struct t_vpi_value arg_value;
   int inst, instAddr;

   /* get a handle to the first argument to $list_nets */
   systf_handle = vpi_handle(vpiSysTfCall, NULL);
   arg_iterator = vpi_iterate(vpiArgument, systf_handle);

   // Grab the value of the first argument (inst)
   arg_handle = vpi_scan(arg_iterator);
   arg_value.format = vpiIntVal;
   vpi_get_value(arg_handle, &arg_value);
   inst = arg_value.value.integer;

   // Grab the value of the second argument (inst)
   arg_handle = vpi_scan(arg_iterator);
   arg_value.format = vpiIntVal;
   vpi_get_value(arg_handle, &arg_value);
   instAddr = arg_value.value.integer;

   proc.load(inst, instAddr);

   vpi_free_object(arg_iterator);
   return 0;
}

static int processor_readReg(char*user_data)
{
   vpiHandle systf_handle, arg_iterator, arg_handle;
   struct t_vpi_value arg_value;
   int regNumber, regValue;

   /* get a handle to the first argument to $list_nets */
   systf_handle = vpi_handle(vpiSysTfCall, NULL);
   arg_iterator = vpi_iterate(vpiArgument, systf_handle);

   // Grab the value of the first argument (regValue)
   arg_handle = vpi_scan(arg_iterator);
   arg_value.format = vpiIntVal;
   vpi_get_value(arg_handle, &arg_value);
   regNumber = arg_value.value.integer;

   proc.readReg(regNumber, regValue);

   // Grab the value of the third argument (din)
   arg_handle = vpi_scan(arg_iterator);
   arg_value.format = vpiIntVal;
   arg_value.value.integer = regValue;
   vpi_put_value(arg_handle, &arg_value, NULL, vpiNoDelay);

   vpi_free_object(arg_iterator);
   return 0;
}

static int processor_clock(char*user_data)
{
   proc.clock();
   return 0;
}

void register_processor()
{
   s_vpi_systf_data tf_data;

   tf_data.type      = vpiSysTask;
   tf_data.compiletf = NULL;
   tf_data.sizetf    = 0;
   tf_data.user_data = 0;

   tf_data.tfname    = "$processor_clock";
   tf_data.calltf    = processor_clock;
   vpi_register_systf(&tf_data);

   tf_data.tfname    = "$processor_load";
   tf_data.calltf    = processor_load;
   vpi_register_systf(&tf_data);

   tf_data.tfname    = "$processor_readReg";
   tf_data.calltf    = processor_readReg;
   vpi_register_systf(&tf_data);
}

void (*vlog_startup_routines[])() = {
    register_processor,
    0
};