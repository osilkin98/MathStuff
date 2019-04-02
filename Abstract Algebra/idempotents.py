
def find_idempotents(n: int) -> list:
    return [a for a in range(n) if a % n == (a**2) % n]

def idempotent_lists(n_start: int, n_end: int, step: int) -> list:
    assert n_start > 1 and step > 0
    return [(n, find_idempotents(n)) for n in range(n_start, n_end + 1, step)]

def print_idempotent_info(n: int, idempotents: list):
    print(f"The following are all idempotent in {n}:")
    for e in idempotents:
        print(f"{e}: {e}² = {e**2} = {e} + {e**2 - e} = {e} + {12}*{(e**2 - e)//12}")

def show_idempotents(n_start: int, n_end: int, step: int = 1):
    idempotents = idempotent_lists(n_start, n_end, step)
    for mod_n, idems in idempotents:
        print_idempotent_info(mod_n, idems)
        print('-'*80)

if __name__ == '__main__':
    show_idempotents(2, 36)
