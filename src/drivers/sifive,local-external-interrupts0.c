/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/io.h>
#include <mee/drivers/sifive,local-external-interrupts0.h>

void __mee_driver_sifive_local_external_interrupt_init(struct mee_interrupt *controller)
{
    struct __mee_driver_sifive_local_external_interrupts0 *local0;

    local0 = (struct __mee_driver_sifive_local_external_interrupts0 *)(controller);
    if ( !local0->init_done ) {
        struct mee_interrupt *intc = local0->interrupt_parent;

	/* Register its interruptswith with parent controller, aka all external to default isr */
        for (int i = 0; i < local0->num_interrupts; i++) {
	  intc->vtable->interrupt_register(intc,
					   local0->interrupt_lines[i],
					   NULL, local0);
	}
        local0->init_done = 1;
    }
}

int __mee_driver_sifive_local_external_interrupt_register(struct mee_interrupt *controller,
                                                          int id, mee_interrupt_handler_t isr,
                                                          void *priv)
{
    int rc = -1;
    struct __mee_driver_sifive_local_external_interrupts0 *local0 =
                              (struct __mee_driver_sifive_local_external_interrupts0 *)(controller);

    if (id != 0) {
        struct mee_interrupt *intc = local0->interrupt_parent;

        /* Enable its interrupts with parent controller */
        if (intc) {
            rc = intc->vtable->interrupt_register(intc, id, isr, priv);
        }
    }
    return rc;
}

int __mee_driver_sifive_local_external_interrupt_enable(struct mee_interrupt *controller, int id)
{
    int rc = -1;
    struct __mee_driver_sifive_local_external_interrupts0 *local0 =
                              (struct __mee_driver_sifive_local_external_interrupts0 *)(controller);

    if (id != 0) {
        struct mee_interrupt *intc = local0->interrupt_parent;

        /* Enable its interrupts with parent controller */
        if (intc) {
            rc = intc->vtable->interrupt_enable(intc, id);
        }
    }
    return rc;
}

int __mee_driver_sifive_local_external_interrupt_disable(struct mee_interrupt *controller, int id)
{
    int rc = -1;
    struct __mee_driver_sifive_local_external_interrupts0 *local0 =
                              (struct __mee_driver_sifive_local_external_interrupts0 *)(controller);

    if (id != 0) {
        struct mee_interrupt *intc = local0->interrupt_parent;

        /* Enable its interrupts with parent controller */
        if (intc) {
            rc = intc->vtable->interrupt_disable(intc, id);
        }
    }
    return rc;
}

int __mee_driver_sifive_local_external_command_request (struct mee_interrupt *controller,
                                                        int command, void *data)
{
    int index;
    int rc = -1;
    struct __mee_driver_sifive_local_external_interrupts0 *local0 =
                              (struct __mee_driver_sifive_local_external_interrupts0 *)(controller);

    switch (command) {
    case MEE_MAX_INTERRUPT_GET:
        rc = local0->num_interrupts;    
        break;
    case MEE_INDEX_INTERRUPT_GET:
        rc = 0;
        if (data) {
            index = *(int *)data;
            rc = local0->interrupt_lines[index];
        }
        break;
    default:
        break;
    }

    return rc;
}

