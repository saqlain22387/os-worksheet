global port_out
global port_in

port_out:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

port_in:
    mov dx, [esp + 4]
    in al, dx
    ret

