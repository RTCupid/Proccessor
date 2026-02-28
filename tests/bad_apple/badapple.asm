start:
    push 6563
    pop CX

next_frame:
    draw_frame
    push 15
    sleep
    push CX
    push 1
    sub
    pop CX
    push CX
    push 0
    jne next_frame:

    hlt
