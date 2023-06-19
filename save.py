stack = []
ni=5
ci=0
while ci < ni:
    if ci == 0:
        stack.append(100.000000)
        ci+=1
    if ci == 1:
        stack.append(1.000000)
        ci+=1
    if ci == 2:
        a = stack.pop()
        b = stack.pop()
        stack.append(int(b - a))
        ci+=1
    if ci == 3:
        print(int(stack[len(stack) - 1]))
        ci+=1
    if ci == 4:
        if stack[len(stack) - 1] > 0:
            ci=1
        else:
            ci+=1
