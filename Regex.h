#define MAX 2000000000
#define MAX_CHAR 128

class Regex
{
public:

    struct local_regex
    {
        int min;
        int max;

        char type;
        char* str;
        int leng;
        bool* flags;

        int min_pos;
        int max_pos;
    };

    struct answer
    {
        int min;
        int max;

        int cursor;
    };

    int regex_size(char* regex)
    {
        int i2 = 0, i3;
        
        while (regex[i2] != '\0')
        {
            if (regex[i2] == '[')
            {
                i3 = i2;
                i2 += 1;
                while (1)
                { 
                    int max = i2 + 4;
                    for (i2; i2 < max; i2 += 1)
                        if (regex[i2] == '\0')
                        {
                            cout << "Opened '[' at " << i3 << " not closed!\n";
                            return -1;
                        }

                    i2 -= 1;
                    if (regex[i2] == ']')
                        break;
                    else
                    {
                        if (regex[i2] != '|' and regex[i2] != '~')
                        {
                            cout << "Unexpected value '" << regex[i2] << "' at " << i2 << endl;
                            return -1;
                        }
                        else
                            i2 += 1;
                    }
                }

            }

            if (regex[i2] == '(')
            {
                i3 = i2;
                i2 += 1;

                while (regex[i2] != ')')
                {
                    
                        if (regex[i2] == '\0')
                        {
                            cout << "Opened '(' at " << i3 << " not closed!\n";
                            return -1;
                        }
                    i2 += 1;
                }
            }
            
            i2 += 1;
            i3 = i2;
            while (regex[i2] != '(' and regex[i2] != '[' and regex[i2] != '\0')
                i2 += 1;

            if(i2 == i3)
            {
                cout << "Expected number(s) at " << i3 << "\n";
                return -1;
            }
        }

        int size = 0;
        int i = 0;

        while (regex[i] != '\0')
        {
            if (regex[i] == '[')
            {
                i = i + 1;
                while (1)
                {
                    int first = regex[i];
                    i += 1;
                    if (regex[i] != '-')
                    {
                        cout << "Char '-' was expected at " << i << endl;
                        return -1;
                    }
                    i += 1;
                    int second = regex[i];

                    if (first > second)
                    {
                        cout << "First char '" << first << "' bigger than second '" << second << "' at " << i << endl;
                        return -1;
                    }
                    i += 1;

                    if (regex[i] == ']')
                        break;
                    else
                    {
                        if (regex[i] != '|' and regex[i] != '~')
                        {
                            cout << "Unexpected char '" << regex[i] << "' at regex on position " << i << endl;
                            return -1;
                        }
                        else
                            i += 1;
                    }
                }
            }
            else if (regex[i] == '(')
            {
                i = i + 1;
                while (regex[i] != ')')
                    i += 1;
            }
            else
            {
                cout << "Unexpected char '" << regex[i] << "' at regex on position " << i << endl;
                return -1;
            }

            i += 1;
            while (regex[i] >= '0' and regex[i] <= '9')
                i += 1;

            if (regex[i] == '+')
                i += 1;
            else
            {
                if (regex[i] == '-')
                {
                    i += 1;

                    while (regex[i] >= '0' and regex[i] <= '9')
                        i += 1;
                }
            }

            if (regex[i] != '[' and regex[i] != '(' and regex[i] != '\0')
            {
                cout << "Expected '[' or '(' at " << i << endl;
                return -1;
            }
            size += 1;
        }

        return size;
    }

    bool regex_cmp(char* arg, char* regex)
    {
        int size = regex_size(regex);

        if (size < 1)
        {
            cout << "There are some failes in regex!\n";
            return false;
        }

        int arg_ppt = 0, reg_ppt = 0;

        /*
        *    Preparing regex string to array of local regex
        *    Types:
        *       "string"N - text string
        *       [A-C]N - from A to C N times
        *
        */
        struct local_regex * reg_arr;
        reg_arr = new local_regex[size];
 
        int i = 0;
        char* buff = new char[length(regex) + 1];

        while (regex[reg_ppt] != '\0')
        {
            if (regex[reg_ppt] == '(')
            {
                reg_arr[i].type = 's';
                int i2 = 0;
                reg_ppt += 1;

                while (regex[reg_ppt] != ')' and regex[reg_ppt] != '\0')
                {
                    buff[i2] = regex[reg_ppt];
                    reg_ppt += 1;
                    i2 += 1;
                }

                buff[i2] = '\0';
                reg_arr[i].leng = i2;
                reg_arr[i].str = copy_str(buff);
                reg_ppt += 1;
            }
            else if (regex[reg_ppt] == '[')
            {
                reg_arr[i].type = 'f';
                reg_ppt += 1;
                int i3;

                reg_arr[i].flags = new bool[MAX_CHAR];

                for (i3 = 0; i3 < MAX_CHAR; i3 += 1)
                    reg_arr[i].flags[i3] = false;

                bool inv = false;

                while (1)
                {
                    char min, max;
                    min = regex[reg_ppt];
                    reg_ppt += 2;
                    max = regex[reg_ppt];

                    bool invert_inv = !inv;

                    for (i3 = min; i3 <= max; i3 += 1)
                        reg_arr[i].flags[i3] = invert_inv;

                    reg_ppt += 1;
                    if (regex[reg_ppt] == '~')
                        inv = true;
                    else if (regex[reg_ppt] == '|')
                        inv = false;
                    else if (regex[reg_ppt] == ']')
                        break;
                    reg_ppt += 1;
                }
                reg_ppt += 1;
            };

            answer ans = get_size(reg_ppt, regex);
            reg_arr[i].min = ans.min;
            reg_arr[i].max = ans.max;
            reg_ppt = ans.cursor;
            i += 1;
        };
        delete[] buff;

        int st_reg, fn_reg, st_str, fn_str;
        st_reg = 0;
        fn_reg = size - 1;
        st_str = 0;
        fn_str = length(arg) - 1;

        bool result;
        result = regex_procedure(reg_arr, size, st_reg, fn_reg, arg, st_str, fn_str);
        delete_regex(reg_arr, size);
        return result;
    }


private:

    int get_free_space(int field_size, int min, int max)
    {
        int first = field_size - min + 1;
        int second = field_size - max + 1;
        if (second < 1)
            second = 1;

        int res = (first + second) * (first - second + 1) / 2;
        return res;
    }

    bool is_here(struct local_regex reg, char* arg, int size, int start)
    {
        int i, i2;
        if (reg.type == 's')
        {
            for (i = 0; i < size; i += 1)
            {
                for (i2 = 0; i2 < reg.leng; i2 += 1)
                {
                    if (reg.str[i2] != arg[start])
                        return false;
                    start += 1;
                }
            }
        }
        else
        {
            for (i = 0; i < size; i += 1)
            {
                i2 = arg[start];
                if (reg.flags[i2] == false)
                    return false;
                start += 1;
            }
        }
        return true;
    };

    bool is_connect(struct local_regex arg_1, struct local_regex arg_2)
    {
        if (arg_1.type == 'f')
        {
            if (arg_2.type == 's')
            {
                int buff = arg_2.str[0];
                if (arg_1.flags[buff] == true)
                    return true;
                else
                    return false;
            }
            else
            {
                int i;
                for (i = 0; i < MAX_CHAR; i += 1)
                {
                    if (arg_1.flags[i] == true and arg_2.flags[i] == true)
                        return true;
                }
                return false;
            }
        }
        else
        {
            if (arg_2.type == 's')
            {
                if (arg_1.str[0] == arg_2.str[0])
                    return true;
                else
                    return false;
            }
            else
            {
                int buff = arg_1.str[0];
                if (arg_2.flags[buff] == true)
                    return true;
                else
                    return false;
            }
        }
    }

    bool regex_procedure(struct local_regex * regex, int size, int st_reg, int fn_reg, char* arg, int st_str, int fn_str)
    {
        int i;
        for (st_reg; st_reg <= fn_reg; st_reg += 1)
        {
            int st_str_past = st_str;
            bool ans;
            if (st_reg == fn_reg)
                ans = false;
            else
                ans = is_connect(regex[st_reg], regex[st_reg + 1]);

            if (regex[st_reg].type == 'f')
            {
                if (regex[st_reg].min == regex[st_reg].max)
                {
                    int max_ppt = st_str + regex[st_reg].min - 1;
                    if (max_ppt > fn_str)
                        return false;
                    else
                    {
                        for (st_str; st_str <= max_ppt; st_str += 1)
                        {
                            int buff = arg[st_str];
                            if (regex[st_reg].flags[buff] == false)
                                return false;
                        }
                    }
                }
                else
                {
                    if (ans == false)
                    {
                        int count = 0;
                        int buff = arg[st_str];
                        while (st_str <= fn_str and regex[st_reg].flags[buff] == true)
                        {
                            st_str += 1;
                            count += 1;
                            buff = arg[st_str];
                        }

                        if (count < regex[st_reg].min or count > regex[st_reg].max)
                            return false;
                    }
                    else
                    {
                        st_str = st_str_past;
                        break;
                    }
                }
            }
            else
            {
                if (regex[st_reg].min == regex[st_reg].max)
                {
                    for (i = 0; i < regex[st_reg].min; i += 1)
                    {
                        int max_ppt = st_str + regex[st_reg].leng - 1;
                        if (max_ppt > fn_str)
                            return false;
                        else
                        {
                            int i2 = 0;
                            for (st_str; st_str <= max_ppt; st_str += 1)
                            {
                                if (arg[st_str] != regex[st_reg].str[i2])
                                    return false;
                                i2 += 1;
                            }
                        }
                    }
                }
                else
                {
                    if (ans == false)
                    {
                        int count = 0;

                        while (st_str <= fn_str and arg[st_str] == regex[st_reg].str[0])
                        {
                            int i2 = 0;
                            for (i2 = 0; i2 < regex[st_reg].leng; i2 += 1)
                            {
                                if (arg[st_str] != regex[st_reg].str[i2])
                                    return false;
                                st_str += 1;
                            }
                            count += 1;
                        }

                        if (count < regex[st_reg].min or count > regex[st_reg].max)
                            return false;
                    }
                    else
                    {
                        st_str = st_str_past;
                        break;
                    }
                }
            }
        }

        if (st_reg > fn_reg)
        {
            if (st_str > fn_str)
                return true;
            else
                return false;
        }
        else
        {
            int min, max, leng;
            min = st_str;
            max = st_str;

            for (i = st_reg; i <= fn_reg; i += 1)
            {
                if (regex[i].type == 'f')
                    leng = 1;
                else
                    leng = regex[i].leng;

                regex[i].min_pos = min;
                regex[i].max_pos = max + regex[i].max * leng - 1;

                min += regex[i].min * leng;
                max += regex[i].max * leng;
            }

            max = fn_str;
            min = fn_str;
            for (i = fn_reg; i >= st_reg; i -= 1)
            {
                if (regex[i].type == 'f')
                    leng = 1;
                else
                    leng = regex[i].leng;

                int max_pos = max;
                int min_pos = min - regex[i].max * leng + 1;

                if (regex[i].min_pos < min_pos)
                    regex[i].min_pos = min_pos;

                if (regex[i].max_pos > max_pos)
                    regex[i].max_pos = max_pos;

                max -= regex[i].min * leng;
                min -= regex[i].max * leng;
            }

            int min_space = MAX;
            int min_sp_index;

            for (i = fn_reg; i >= st_reg; i -= 1)
            {
                int buff = get_free_space(regex[i].max_pos - regex[i].min_pos + 1, regex[i].min, regex[i].max);
                if (buff < min_space)
                    min_space = buff;
                min_sp_index = i;
            }

            int ind = min_sp_index;
            for (i = regex[ind].min; i <= regex[ind].max; i += 1)
            {
                if (regex[ind].type == 'f')
                    leng = 1;
                else
                    leng = regex[ind].leng;

                int fn_point = regex[ind].max_pos - i * leng + 1;
                if (fn_point < regex[ind].min_pos)
                    break;

                for (int st_point = regex[ind].min_pos; st_point <= fn_point; st_point += 1)
                {
                    bool ans = is_here(regex[ind], arg, i, st_point);
                    if (ans == true)
                    {
                        int max_point = st_point - 1;
                        int min_point = st_point + i;

                        int min_reg = ind + 1;
                        int max_reg = ind - 1;

                        bool ans_fir, ans_sec;

                        if (st_reg <= max_reg)
                            ans_fir = regex_procedure(regex, size, st_reg, max_reg, arg, st_str, max_point);
                        else
                            ans_fir = true;

                        if (ans_fir == true)
                        {
                            if (min_reg <= fn_reg)
                                ans_sec = regex_procedure(regex, size, min_reg, fn_reg, arg, min_point, fn_str);
                            else
                                ans_sec = true;

                            if (ans_sec == true)
                            {
                                return true;
                            }
                        }
                    }
                }
            }

            return false;
        }
    }

    answer get_size(int cursor, char* regex)
    {
        answer ans;

        int i, buff;
        buff = 0;
        i = cursor;

        while (regex[i] >= '0' and regex[i] <= '9')
        {
            buff *= 10;
            buff += regex[i] - '0';
            i += 1;
        }
        ans.min = buff;
        if (regex[i] != '-')
        {
            if (regex[i] == '+')
            {
                ans.max = MAX;
                i += 1;
            }
            else
                ans.max = ans.min;
        }
        else
        {
            i += 1;
            buff = 0;
            while (regex[i] >= '0' and regex[i] <= '9')
            {
                buff *= 10;
                buff += regex[i] - '0';
                i += 1;
            }
            ans.max = buff;
        }

        ans.cursor = i;
        return ans;
    }

    void delete_regex(struct local_regex * reg_arr, int size)
    {
        //cout << "start\n";
        for (int i = 0; i < size; i += 1)
        {
            if (reg_arr[i].type == 's')
                delete[] reg_arr[i].str;

            if (reg_arr[i].type == 'f')
                delete[] reg_arr[i].flags;
        }

        delete [] reg_arr;
        //cout << "finish\n";
    }
};