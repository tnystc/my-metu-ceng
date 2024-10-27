
def check_month(month):
    error_list = []

    #mother rule 1
    def m_check(month):
        if month.count("m") == 0:
            return 0

        enumerated = enumerate(month)

        m_days = [m[0] for m in list(enumerated) if m[1] == "m"]
        m_mod5 = [0 for i in range(len(m_days)-1) if ((m_days[i+1]-m_days[i]) % 5) == 0]
        
        if len(m_mod5) != (len(m_days) - 1):
            return 1
        else:
            return 0
        

    #father rule 2
    def f_check(month):
        if month.count("f") == 0:
            return 0
        
        enumerated = enumerate(month)

        if month.count("f") > 2:
            return 2

        f_days = [f[0] for f in enumerated if f[1] == "f"]
        f_diff = [0 for i in range(len(f_days)-1) if f_days[i+1]-f_days[i] == 1 and (f_days[i+1]%5 != 0 and f_days[i]%5 != 4)]
        if len(f_diff) != 0:
            return 2
        
        return 0

    #skipping babysitter because she is always available

    #grandma rule 4
    def g_check(month):
        if month.count("g") == 0:
            return 0
        
        enumerated = enumerate(month)

        g_days = [g[0] for g in enumerated if g[1] == "g"]
        wednesday_count = [0 for i in range(len(g_days)) if g_days[i] % 5 == 2]
        if len(wednesday_count) > 1:
            return 4
       
        return 0 
    

    #aunt1 rule 5
    def a1_check(month):
        enumerated = enumerate(month)

        global a1_days
        a1_days = [a1[0] for a1 in enumerated if a1[1] == "a1"]

        if len(a1_days) == 0:
            return 0

        wrong_day_detect = [0 for i in range(len(a1_days)) if a1_days[i] % 5 != 1 and a1_days[i] % 5 != 4]
        if len(wrong_day_detect) > 0:
            return 5
       
        return 0 
        
  
    #aunt2 rule 6
    def a2_check(month, a1_days):
        if month.count("a2") == 0:
            return 0
        
        enumerated = enumerate(month)

        a2_days = [a2[0] for a2 in enumerated if a2[1] == "a2"]
        a2_minus_one = [a2_days[i] - 1 for i in range(len(a2_days)) if a2_days[i]%5 != 0]
        match = [x for x in a2_minus_one if x in a1_days]
        if match:
            return 6

        return 0
    
    
    #neighbour lady rule 7
    def n_check(month):
        if month.count("n") == 0:
            return 0
        
        enumerated = enumerate(month)

        n_days = [n[0] for n in enumerated if n[1] == "n"]
        wrong_day_detect = [0 for i in range(len(n_days)) if n_days[i] % 5 != 0 and n_days[i] % 5 != 1 and n_days[i] % 5 != 2]
        if len(wrong_day_detect) > 0:
            return 7
       
        return 0
        
    #appending errors
    if m_check(month) == 1:
        error_list.append(1)
        
    if f_check(month) == 2:
        error_list.append(2)
    
    if g_check(month) == 4:
        error_list.append(4)
    
    if a1_check(month) == 5:
        error_list.append(5)
    
    if a2_check(month, a1_days) == 6:
        error_list.append(6)
    
    if n_check(month) == 7:
        error_list.append(7)

    #function for calculating the total cost
    def calculate(month):
        m_cost = 10 * month.count("m")
        f_cost = 20 * month.count("f")
        g_cost = 50 * month.count("g")
        a1_cost = 32 * month.count("a1")
        a2_cost = 27 * month.count("a2")
      
        #neighbour lady
        n_cost = sum([5 ** i for i in range(1,month.count("n"))])

        #babysitter
        enumerated = enumerate(month)
        b_days = [b[0] for b in enumerated if b[1] == "b"]
        intervening_weekdays = sum([b_days[i+1] - b_days[i] - 1 for i in range(len(b_days)-1) if b_days[i+1]-b_days[i]-1<3 and b_days[i+1]-b_days[i] != 1 and (b_days[i+1]%5 > b_days[i]%5)])
        intervening_weekend = sum([2 for i in range(len(b_days)-1) if b_days[i+1] % 5 == 0 and b_days[i+1]-b_days[i] == 1])
        b_cost = (intervening_weekdays + intervening_weekend + month.count("b")) * 30

        total = m_cost + f_cost + g_cost + a1_cost + a2_cost + n_cost + b_cost

        return total


    #result
    if len(error_list) != 0:
        return error_list
    else:
        return calculate(month)
    
    
