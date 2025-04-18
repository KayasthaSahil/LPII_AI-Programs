import heapq

N = 3  # Puzzle size

def get_input(prompt):
    print(prompt, "(Enter 9 numbers row-wise, use 0 for blank):")
    board = []
    for i in range(N):
        row = list(map(int, input().split()))
        board.append(row)
    return board

def find_zero(state):
    for i in range(N):
        for j in range(N):
            if state[i][j] == 0:
                return (i, j)
    return (-1, -1)  # Should never reach here if input is valid

def misplaced_tiles(state, goal):
    count = 0
    for i in range(N):
        for j in range(N):
            if state[i][j] != 0 and state[i][j] != goal[i][j]:
                count += 1
    return count

def get_moves(x, y):
    moves = []
    if x > 0:
        moves.append((x - 1, y))  # Up
    if x < N - 1:
        moves.append((x + 1, y))  # Down
    if y > 0:
        moves.append((x, y - 1))  # Left
    if y < N - 1:
        moves.append((x, y + 1))  # Right
    return moves

def apply_move(state, zero_pos, new_zero_pos):
    x1, y1 = zero_pos
    x2, y2 = new_zero_pos
    new_state = []
    for row in state:
        new_row = row.copy()
        new_state.append(new_row)
    # Swap zero with the target tile
    temp = new_state[x1][y1]
    new_state[x1][y1] = new_state[x2][y2]
    new_state[x2][y2] = temp
    return new_state

def serialize(state):
    serialized = []
    for row in state:
        serialized.append(tuple(row))
    return tuple(serialized)

def reconstruct_path(parents, current):
    path = []
    while current is not None:
        path.append(current)
        current = parents.get(serialize(current))
    path.reverse()
    return path

def solve_puzzle(start, goal):
    start_zero = find_zero(start)
    start_h = misplaced_tiles(start, goal)
    open_list = []
    heapq.heappush(open_list, (start_h, 0, start, start_zero))
    visited = set()
    parents = {}
    parents[serialize(start)] = None

    while len(open_list) > 0:
        current_f, current_g, current_state, current_zero = heapq.heappop(open_list)

        if current_state == goal:
            print("\nSolution Found!")
            path = reconstruct_path(parents, current_state)
            for step in path:
                for row in step:
                    for value in row:
                        print(value, end=' ')
                    print()
                print("------")
            return

        visited.add(serialize(current_state))

        possible_moves = get_moves(current_zero[0], current_zero[1])
        for move in possible_moves:
            new_state = apply_move(current_state, current_zero, move)
            if serialize(new_state) in visited:
                continue

            new_g = current_g + 1
            new_h = misplaced_tiles(new_state, goal)
            new_f = new_g + new_h

            serialized_new = serialize(new_state)
            if serialized_new not in parents:
                parents[serialized_new] = current_state
                heapq.heappush(open_list, (new_f, new_g, new_state, move))

    print("No solution found.")

# Main driver
start_state = get_input("Enter the initial state")
goal_state = get_input("Enter the goal state")
print("Solving the 8-Puzzle using A* Algorithm...")
solve_puzzle(start_state, goal_state)
