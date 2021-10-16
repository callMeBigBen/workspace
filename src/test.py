import copy

input = [1,2,3,7,5,6]
2

def solve(input):
    size = len(input)
    u = copy.copy(input)
    u.sort()
    N = 0
    for i in range(0, size):
        if i==0 or u[i]>u[i-1]:
              u[N] = u[i]
              N += 1
    dp = [0] * N
    for i in range(0, size):
        opt = float('inf')
        for j in range(0, N):
            opt = min(opt, dp[j])
            dp[j] = opt + abs(input[i] - u[j])
    opt = float('inf')
    for i in range(0, N):
        opt = min(opt, dp[i])
    return opt


def minCost(input):
    if len(input) <= 2:
        return 0
    ret = solve(input)
    for i in range(0, len(input)):
        input[i] = -input[i]
    return min(ret, solve(input))
    input2 = copy.copy(input)
    input2.sort()
    min_cost_ascending = 0
    min_cost_descending = 0;
    for i in range(0, len(input)):
        min_cost_ascending += abs(input[i] - input2[i])
    for i in range(0, len(input)):
        min_cost_descending += abs(input[i] - input2[len(input) - i - 1])
    return min(min_cost_ascending, min_cost_descending)
    # for i in range(1, len(input) - 1):
    #     if input[i] > input[i - 1] and input[i] > input[i + 1]:
    #         min_cost_ascending += min(input[i] - input[i - 1], input[i] - input[i + 1])
    #         input[i] = max(input[i - 1], input[i + 1])
    #     elif input[i] < input[i-1]:
    #         min_cost_ascending += input[i-1] - input[i]
    #         input[i] = input[i-1]
    # if len(input) > 1:
    #     min_cost_ascending += max(0, input[-2] - input[-1])
    # for i in range(1, len(input2) - 1):
    #     if input2[i] < input2[i - 1] and input2[i] < input2[i + 1]:
    #         min_cost_descending += min(input2[i - 1] - input2[i], input2[i + 1] - input2[i])
    #         input2[i] = min(input2[i - 1], input2[i + 1])
    #     elif input2[i] > input2[i-1]:
    #         min_cost_descending += input[i] - input[i - 1]
    #         input[i] = input[i-1]
    # if len(input2) > 1:
    #     min_cost_descending += max(0, abs(input[-2] - input[-1]))
    

print minCost(input)