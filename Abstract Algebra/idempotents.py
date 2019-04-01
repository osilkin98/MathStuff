
def get_idempotents(n: int) -> list:
    return [a for a in range(n) if a % n == (a**2) % n]

if __name__ == '__main__':
    try:
        n = int(input("Specify the n for congruency ring\nn:  "))
        idempotents = get_idempotents(n)
        print(f"The following are all idempotent in {n}:")
        for e in idempotents:
            print(f"{e}: {e}² = {e**2} = {e} + {e**2 - e} = {e} + {12}*{(e**2 - e)//12}")
    except TypeError:
        from time import sleep
        print("\WhOOPsIE DAIsy LOokS liKE yOU maDE a MIstAKe. ")
        sleep(0.6)
        print("Aww Shucks We'RE not gonna tell you ANYTHING ABOUT THIS ER7ROR")
        sleep(0.3)
        print("EVEN IF IT MIGHT BE HELPFUL!!!!!!!!!!!")
    finally:
        print("\ndone.")
