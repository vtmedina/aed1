def longestDiverseString(a: int, b: int, c: int) -> str:
    from heapq import heappush, heappop

    heap = []
    if a > 0:
        heappush(heap, (-a, 'a'))
    if b > 0:
        heappush(heap, (-b, 'b'))
    if c > 0:
        heappush(heap, (-c, 'c'))

    result = []

\\ nao consegui terminar em aula