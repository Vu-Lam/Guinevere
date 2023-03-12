#include "knight.h"
void convIntArr(string line, int a[]) // Chuyển dòng thành mảng số nguyên
{
    string numStr;
    int j = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] != ' ')
        {
            numStr += line[i];
        }
        else
        {
            a[j] = stoi(numStr);
            j++;
            numStr = "";
        }
        if (!numStr.empty())
            a[j] = stoi(numStr);
    }
}
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
    cout << "HP=" << HP
         << ", level=" << level
         << ", remedy=" << remedy
         << ", maidenkiss=" << maidenkiss
         << ", phoenixdown=" << phoenixdown
         << ", rescue=" << rescue << endl;
}
void update(knight hero, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue) // Hàm cập nhật lại chỉ số của hiệp sĩ
{
    HP = hero.HP;                   // Cập nhật HP
    level = hero.level;             // Cập nhật level
    remedy = hero.remdedy;          // Cập nhật remedy
    maidenkiss = hero.maidenkiss;   // Cập nhật maidenkiss
    phoenixdown = hero.phoenixdown; // Cập nhật phoenixdown
    rescue = hero.rescue;           // Cập nhật rescue
}
// Sự kiện số 0
void event_0(knight &hero)
{
    hero.rescue = 1;
}
// Sự kiện từ 1 đến 5
void event_15(knight &hero, int index, int event)
{
    if (!isArthur(hero) && !isLancelot(hero))
    {
        index++;
        int b = index % 10;
        int levelO = index > 6 ? (b > 5 ? b : 5) : b; // index > 6 và b > 5 thì levelO = b , index >6 và b <=5 thì level) = 5 còn lại thì levelO sẽ < 6
        int damage = 0;
        if (hero.level > levelO)
        {
            // Thắng
            if (hero.level < 10)
            {
                hero.level++;
            }
        }
        else if (hero.level < levelO)
        {
            // Giao tranh, tính lại HP
            // gặp gấu MadBear
            if (event == 1)
            {
                // cout << "Call" << endl;
                damage = baseDamage_MadBear * levelO * 10;
                hero.HP = hero.HP - damage;
            }
            // gặp cướp Bandit
            if (event == 2)
            {
                damage = baseDamage_Bandit * levelO * 10;
                hero.HP = hero.HP - damage;
            }
            // gặp tướng cướp LordLupin
            if (event == 3)
            {
                damage = baseDamage_LordLupin * levelO * 10;
                hero.HP = hero.HP - damage;
            }
            // gặp yêu tinh Elf
            if (event == 4)
            {
                damage = baseDamage_Elf * levelO * 10;
                hero.HP = hero.HP - damage;
            }
            // gặp quỷ khổng lồ Troll
            if (event == 5)
            {
                damage = baseDamage_Troll * levelO * 10;
                hero.HP = hero.HP - damage;
            }
        }
    }
}
// Kiểm tra xem hiệp sĩ có "đi" chưa
bool lose(knight &hero)
{
    if (hero.HP <= 0)
    {
        if (hero.phoenixdown == 0)
        {
            return true;
        }
        else
        {
            hero.phoenixdown--;
            hero.HP = hero.max_HP;
            return false;
        }
    }
    else
        return false;
}
// Sự kiện số 6
void event_6(knight &hero, int index, bool &isTiny)
{
    if (!isArthur(hero) && !isLancelot(hero))
    {
        index++;
        int b = index % 10;
        int levelO = index > 6 ? (b > 5 ? b : 5) : b;
        // Thắng
        if (hero.level > levelO)
        {
            if (hero.level < 9)
            {
                hero.level += 2;
            }
            else if (hero.level == 9)
            {
                hero.level += 1;
            }
        }
        // Thua
        else if (hero.level < levelO)
        {
            if (hero.remdedy < 1)
            {
                hero.HP = hero.HP < 5 ? 1 : (hero.HP / 5);
                isTiny = true;
            }
            else
                hero.remdedy--;
        }
    }
    else
    {
        if (hero.level < 9)
        {
            hero.level += 2;
        }
        else if (hero.level == 9)
        {
            hero.level += 1;
        }
    }
}
// Check hết biến thành tí hon
bool endTiny(knight &hero, int index, int check_event6_end, bool isTiny)
{
    if ((index - check_event6_end == 3 && isTiny))
        return true;
    else if (hero.remdedy > 0 && isTiny)
    {
        hero.remdedy--;
        return true;
    }
    return false;
}
// Sự kiện số 7
void event_7(knight &hero, int index)
{
    if (!isArthur(hero) && !isLancelot(hero))
    {
        index++;
        int b = index % 10;
        int levelO = index > 6 ? (b > 5 ? b : 5) : b;
        if (hero.level > levelO)
        {
            // Thắng
            if (hero.level < 9)
            {
                hero.level += 2;
            }
            else if (hero.level == 9)
            {
                hero.level += 1;
            }
        }
        else if (hero.level < levelO)
        {
            becomeFrog(hero);
        }
    }
    else
    {
        if (hero.level < 9)
        {
            hero.level += 2;
        }
        else if (hero.level == 9)
        {
            hero.level += 1;
        }
    }
}
// Biến thành ếch
void becomeFrog(knight &hero)
{
    if (hero.maidenkiss > 0)
    {
        hero.maidenkiss--;
    }
    else
    {
        hero.level = 1;
    }
}
// Sự kiện số 11
void event_11(knight &hero)
{
    int n1 = ((hero.level + hero.phoenixdown) % 5 + 1) * 3;
    int s1 = 0;
    for (int i = 0; i < n1; i++)
    {
        s1 += 99 - 2 * i;
    }
    hero.HP = hero.HP + (s1 % 100);
    do
    {
        hero.HP++;
    } while (!isPrime(hero.HP));
    if (hero.HP > hero.max_HP)
    {
        hero.HP = hero.max_HP;
    }
}
// Kiểm tra số nguyên tố
bool isPrime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}
// Sự kiện số 12
void event_12(knight &hero)
{
    if (hero.HP > 1)
    {
        while (!isFibonacci(hero.HP))
        {
            hero.HP--;
        }
    }
}
// Kiểm tra số Fibonacci
bool isFibonacci(int n)
{
    int ar[16];
    ar[0] = 1;
    ar[1] = 1;
    for (int i = 2; i < 17; i++)
    {
        ar[i] = ar[i - 1] + ar[i - 2];
        if (n == ar[i])
        {
            return true;
        }
    }
    return false;
}
// Sự kiện số 13
void event_13(knight &hero, int mush_type, string file_mush_ghost)
{
    string line1, line2;
    ifstream filein(file_mush_ghost);
    // Nhận thông tin dòng đầu
    getline(filein, line1);
    // Chuyển thông tin thành số
    int n = stoi(line1);
    // Reset các chỉ số trước khi ăn nấm
    if (hero.HP > hero.max_HP)
    {
        hero.HP = hero.max_HP;
    }
    // Tiến hành ăn nấm
    switch (mush_type)
    {
    case 1: // Nấm loại 1
    {
        // Khởi tạo mảng chứa dãy số dòng 2
        int arr[n];
        // Nhận thông tin dòng 2 vào mảng thông qua string
        string intStr;
        for (int i = 0; i < n; i++)
        {
            getline(filein, intStr, ',');
            arr[i] = stoi(intStr);
        }
        int maxi = find_maxi(arr, n);
        int mini = find_mini(arr, n);
        // cout << "Nam so 1, mau bi tru: " << maxi + mini << endl;
        hero.HP = hero.HP - (maxi + mini);
        break;
    }
    case 2: // Nấm loại 2
    {
        // Khởi tạo mảng chứa dãy số dòng 2
        int arr[n];
        // Nhận thông tin dòng 2 vào mảng thông qua string
        string intStr;
        for (int i = 0; i < n; i++)
        {
            getline(filein, intStr, ',');
            arr[i] = stoi(intStr);
        }
        int mtx = 0, mti = 0;
        if (!isMountainArray(arr, n, mtx, mti))
        {
            mtx = -2;
            mti = -3;
        }
        // cout << "Nam so 2, mau bi tru: " << mtx + mti << endl;
        hero.HP = hero.HP - (mtx + mti);
        break;
    }
    case 3: // Nấm loại 3
    {
        // Khởi tạo mảng chứa dãy số dòng 2
        int arr[n];
        // Nhận thông tin dòng 2 vào mảng thông qua string
        string intStr;
        for (int i = 0; i < n; i++)
        {
            getline(filein, intStr, ',');
            arr[i] = stoi(intStr);
        }
        // Khởi tạo mảng mới chứa các số được biến đổi ở dòng 2
        int new_arr[n];
        for (int i = 0; i < n; i++)
        {
            if (arr[i] < 0)
            {
                new_arr[i] = -arr[i];
                new_arr[i] = (17 * new_arr[i] + 9) % 257;
            }
            else
            {
                new_arr[i] = arr[i];
                new_arr[i] = (17 * new_arr[i] + 9) % 257;
            }
        }
        // Tìm maxi2, mini2 trong mảng mới
        int maxi2 = find_maxi2(new_arr, n);
        int mini2 = find_mini2(new_arr, n);
        // cout << "Nam so 3, mau bi tru: " << maxi2 + mini2 << endl;
        hero.HP = hero.HP - (maxi2 + mini2);
        break;
    }
    case 4: // Nấm loại 4
    {
        // Khởi tạo mảng chứa dãy số dòng 2
        int arr[n];
        // Nhận thông tin dòng 2 vào mảng thông qua string
        string intStr;
        for (int i = 0; i < n; i++)
        {
            getline(filein, intStr, ',');
            arr[i] = stoi(intStr);
        }
        // Khởi tạo mảng mới chứa các số được biến đổi ở dòng 2
        int new_arr[n];
        for (int i = 0; i < n; i++)
        {
            if (arr[i] < 0)
            {
                new_arr[i] = -arr[i];
                new_arr[i] = (17 * new_arr[i] + 9) % 257;
            }
            else
            {
                new_arr[i] = arr[i];
                new_arr[i] = (17 * new_arr[i] + 9) % 257;
            }
        }
        // Tìm max2_3x, max2_3i
        int max2_3x, max2_3i;
        // Trường hợp không tồn tại số lớn thứ 2
        if (n < 3 || (new_arr[0] == new_arr[1] && new_arr[1] == new_arr[2]))
        {
            max2_3x = -5;
            max2_3i = -7;
        }
        // Trường hợp tồn tại số lớn thứ 2
        // Trường hợp 3 số nhưng chỉ có 2 giá trị
        if (new_arr[0] == new_arr[1])
        {
            if (new_arr[2] > new_arr[1])
            {
                max2_3x = new_arr[0];
                max2_3i = 0;
            }
            else
            {
                max2_3x = new_arr[2];
                max2_3i = 2;
            }
        }
        if (new_arr[1] == new_arr[2])
        {
            if (new_arr[0] > new_arr[1])
            {
                max2_3x = new_arr[1];
                max2_3i = 1;
            }
            else
            {
                max2_3x = new_arr[0];
                max2_3i = 0;
            }
        }
        if (new_arr[0] == new_arr[2])
        {
            if (new_arr[1] > new_arr[0])
            {
                max2_3x = new_arr[0];
                max2_3i = 0;
            }
            else
            {
                max2_3x = new_arr[1];
                max2_3i = 1;
            }
        }
        // Trường hợp 3 giá trị khác nhau
        if (new_arr[0] != new_arr[1] && new_arr[1] != new_arr[2] && new_arr[0] != new_arr[2])
        {
            max2_3x = new_arr[0];
            max2_3i = 0;
            if (max2_3x < new_arr[1])
            {
                max2_3x = new_arr[1];
                max2_3i = 1;
            }
            if (max2_3x < new_arr[2])
            {
                max2_3x = new_arr[2];
                max2_3i = 2;
            }
            int min_x = new_arr[0], min_i = 0;
            if (min_x > new_arr[1])
            {
                min_x = new_arr[1];
                min_i = 1;
            }
            if (min_x > new_arr[2])
            {
                min_x = new_arr[2];
                min_i = 2;
            }
            max2_3i = 3 - max2_3i - min_i;
            max2_3x = new_arr[max2_3i];
        }
        // cout << "Nam so 4, mau bi tru: " << max2_3i + max2_3x << endl;
        hero.HP = hero.HP - (max2_3x + max2_3i);
        break;
    }
    default:
        break;
    }
    // Đóng file
    filein.close();
}
// Kiểm tra dãy số hình núi
bool isMountainArray(int *arr, int n, int &mtx, int &mti)
{
    bool don_dieu = true;
    // Kiểm tra mảng có giống nhau hết hay không
    // Xem biến đơn điệu là biến để check giống nhau, nếu đơn điệu = 1 thì giống nhau hết
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] != arr[i + 1])
        {
            don_dieu = false;
            break;
        }
    }
    if (don_dieu)
        return false;
    // Kiểm tra luôn tăng hay không
    don_dieu = true;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            don_dieu = false;
            break;
        }
    }
    if (don_dieu)
    {
        mtx = arr[n - 1];
        mti = n - 1;
        return true;
    }
    // Kiểm tra có luôn giảm không
    don_dieu = true;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            don_dieu = false;
            break;
        }
    }
    if (don_dieu)
    {
        mtx = arr[0];
        mti = 0;
        return true;
    }
    // Nếu không đơn điệu thì đi đếm đỉnh
    int count = 0;
    // Kiểm tra 2 đầu của mảng có phải đỉnh hay không
    if (arr[0] > arr[1])
        count++;
    if (arr[n - 2] < arr[n - 1])
        count++;
    // Kiểm tra trong khoảng giữa 2 đầu có đỉnh hay không
    for (int i = 1; i < n - 1; i++)
    {
        if (arr[i - 1] < arr[i] && arr[i] > arr[i + 1])
        {
            count++;
            mtx = arr[i];
            mti = i;
        }
    }
    if (count > 1)
        return false;
    else
        return true;
}
// Tìm vị trí lớn nhất
int find_maxi(int arr[], int n)
{
    int max = arr[0];
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (max <= arr[i])
        {
            max = arr[i];
            flag = i;
        }
    }
    return flag;
}
// Tìm vị trí nhỏ nhất
int find_mini(int arr[], int n)
{
    int min = arr[0];
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (min >= arr[i])
        {
            min = arr[i];
            flag = i;
        }
    }
    return flag;
}
// Tìm vị trí max2
int find_maxi2(int arr[], int n)
{
    int max = arr[0];
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
            flag = i;
        }
    }
    return flag;
}
// Tìm vị trí min2
int find_mini2(int arr[], int n)
{
    int min = arr[0];
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (min > arr[i])
        {
            min = arr[i];
            flag = i;
        }
    }
    return flag;
}
// Sự kiện số 19
void event_19(knight &hero, string file_asclepius_pack)
{
    string line1, line2;
    ifstream filein(file_asclepius_pack);
    // Đọc 2 dòng đầu vào
    getline(filein, line1);
    getline(filein, line2);
    // Khởi tạo mảng chứa ma trận
    int arr[stoi(line1)][stoi(line2)];
    // Đọc vào ma trận từ file
    for (int i = 0; i < stoi(line1); i++)
    {
        for (int j = 0; j < stoi(line2); j++)
        {
            filein >> arr[i][j];
        }
    }
    int count_in_line = 0;
    for (int i = 0; i < stoi(line1); i++)
    {
        for (int j = 0; j < stoi(line2); j++)
        {
            if (arr[i][j] == 16 && hero.remdedy < Max_remedy && count_in_line < 3)
            {
                hero.remdedy++;
                count_in_line++;
            }
            if (arr[i][j] == 17 && hero.maidenkiss < Max_maidenkiss && count_in_line < 3)
            {
                hero.maidenkiss++;
                count_in_line++;
            }
            if (arr[i][j] == 18 && hero.phoenixdown < Max_phoenixdown && count_in_line < 3)
            {
                hero.phoenixdown++;
                count_in_line++;
            }
        }
        count_in_line = 0;
    }
    filein.close();
}
// Kiểm tra vua Arthur
bool isArthur(knight &hero)
{
    if (hero.max_HP == MaxHP)
        return true;
    else
        return false;
}
// Kiểm tra Lancelot
bool isLancelot(knight &hero)
{
    if (isPrime(hero.max_HP))
        return true;
    else
        return false;
}
// Sự kiện số 99
void event_99(knight &hero)
{
    if ((isArthur(hero)) || (isLancelot(hero) && hero.level > 7) || (hero.level = 10))
    {
        hero.level = 10;
    }
    else
    {
        hero.rescue = 0;
    }
}
// Sự kiện số 18
void event_18(knight &hero, string file_merlin_pack)
{
    // Mở file để đọc
    ifstream file(file_merlin_pack);
    // Đọc số nguyên n từ dòng đầu tiên
    int n;
    file >> n;
    // Tạo một mảng string để lưu trữ các đoạn văn bản
    string *lines = new string[n];
    // Đọc từng dòng trong file và lưu trữ chúng vào mảng string
    getline(file, lines[0]); // bỏ qua dòng đầu tiên
    for (int i = 0; i < n; i++)
    {
        getline(file, lines[i]);
    }
    // Biến này dùng để xem ctrinh sẽ chạy +3HP hay +2HP
    bool plus_3HP = true;
    // Check cộng 3 HP
    // Xét từng dòng
    string check = "";
    for (int i = 0; i < n; i++)
    {
        // Xét từng từ của dòng
        int prev_HP = hero.HP;
        for (int j = 0; j < lines[i].length(); j++)
        {
            if ((64 < lines[i][j] && lines[i][j] < 91) || (96 < lines[i][j] && lines[i][j] < 123))
            {
                check += lines[i][j];
            }
            else
            {
                if (check == "Merlin" || check == "merlin")
                {
                    if (hero.HP + 3 > hero.max_HP)
                    {
                        hero.HP = hero.max_HP;
                    }
                    else
                        hero.HP += 3;
                }
                check = "";
            }
        }
        // Nếu máu trước khi cộng là max or khác với máu hiện tại thì bỏ qua
        if (prev_HP == hero.max_HP || prev_HP != hero.HP)
        {
            continue;
        }
        else // Tiến hành kiểm tra cộng 2 máu
        {
            bool is_m = false, is_e = false, is_r = false, is_l = false, is_i = false, is_n = false;
            // Xét từng từ của dòng
            for (int j = 0; j < lines[i].length(); j++)
            {
                if (isCharacter('m', lines[i][j]))
                    is_m = true;
                if (isCharacter('e', lines[i][j]))
                    is_e = true;
                if (isCharacter('r', lines[i][j]))
                    is_r = true;
                if (isCharacter('l', lines[i][j]))
                    is_l = true;
                if (isCharacter('i', lines[i][j]))
                    is_i = true;
                if (isCharacter('n', lines[i][j]))
                    is_n = true;
            }
            if (is_m && is_e && is_r && is_l && is_i && is_n)
            {
                if (hero.HP + 2 > hero.max_HP)
                {
                    hero.HP = hero.max_HP;
                }
                else
                    hero.HP += 2;
            }
            is_m = false;
            is_e = false;
            is_r = false;
            is_l = false;
            is_i = false;
            is_n = false;
        }
    }
    // Đóng file
    file.close();
    // Giải phóng vùng nhớ của mảng string
    delete[] lines;
}
bool isCharacter(char c, char in_put)
{
    char check_char = c;
    if (in_put == check_char)
        return true;
    else if (check_char < 91)
    {
        check_char += 32;
    }
    else
        check_char -= 32;
    if (in_put == check_char)
        return true;
    else
        return false;
}
void adventureToKoopa(string file_input, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    // Lấy thông tin đầu vào
    string line1, line2, file_mush_ghost, file_asclepius_pack, file_merlin_pack;
    ifstream filein(file_input);
    getline(filein, line1);
    getline(filein, line2);
    getline(filein, file_mush_ghost, ',');
    getline(filein, file_asclepius_pack, ',');
    getline(filein, file_merlin_pack, ',');
    // Cập nhật thông tin cho hiệp sĩ
    int knightInt[5];
    convIntArr(line1, knightInt);
    knight myHero;
    myHero.HP = knightInt[0];
    myHero.level = knightInt[1];
    myHero.remdedy = knightInt[2];
    myHero.maidenkiss = knightInt[3];
    myHero.phoenixdown = knightInt[4];
    myHero.max_HP = knightInt[0];
    myHero.rescue = -1;
    // Khởi tạo mảng số nguyên chứa các sự kiện
    int event[MAX] = {0};
    // Cập nhật giá trị các phần tử cho mảng event, xem như -1 là rỗng
    for (int i = 0; i < MAX; i++)
    {
        event[i] = -1;
    }
    // Cập nhật giá trị của từng event được nhận từ file
    convIntArr(line2, event);
    // Cập nhật thông tin đầu vào cho hiệp sĩ
    update(myHero, HP, level, remedy, maidenkiss, phoenixdown, rescue);
    int checkevent_6_end = -9999; // Biến này dùng để kiểm tra khi nào hiệp sĩ hết 3 vòng event 6
    bool isTiny = false;
    int prev_level;               // Biến này để lưu level trước khi bị biến thành ếch
    int checkevent_7_end = -9999; // Biến này dùng để kiểm tra hiệp sĩ hết biến thành ếch hay chưa
    bool isFrog = false;          // Biến này để kiểm tra có biến thành ếch hay không
    //  Khởi tạo vòng lặp để duyệt qua từng sự kiện của hiệp sĩ
    for (int i = 0; event[i] != -1; i++)
    {
        // Duyệt từng sự kiện
        // Sự kiện 0
        if (event[i] == 0)
        {
            event_0(myHero);
            update(myHero, HP, level, remedy, maidenkiss, phoenixdown, rescue);
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            break;
        }
        // Sự kiện từ 1 tới 5
        else if (event[i] == 1 || event[i] == 2 || event[i] == 3 || event[i] == 4 || event[i] == 5)
        {
            event_15(myHero, i, event[i]);
            if (lose(myHero))
            {
                myHero.rescue = 0;
                update(myHero, HP, level, remedy, maidenkiss, phoenixdown, rescue);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
        }
        // Sự kiện 6
        else if (event[i] == 6)
        {
            event_6(myHero, i, isTiny);
            checkevent_6_end = i;
        }
        // Sự kiện 7
        else if (event[i] == 7)
        {
            prev_level = myHero.level;
            checkevent_7_end = i;
            event_7(myHero, i);
            isFrog = (myHero.level == 1) ? (true) : (false);
        }
        // Sự kiện 11
        else if (event[i] == 11)
        {
            event_11(myHero);
        }
        // Sự kiện 12
        else if (event[i] == 12)
        {
            event_12(myHero);
        }
        // Sự kiện 13
        else if (event[i] > 100)
        {
            // Biến sự kiện 13 thành chuỗi để dễ xử lý
            string s = to_string(event[i]);
            // Khởi tạo vòng lặp để duyệt các loại nấm được ăn vào
            for (int i = 2; s[i] != '\0'; i++)
            {
                // Kiểm tra chết chưa trước khi ăn
                if (lose(myHero))
                {
                    myHero.rescue = 0;
                    break;
                }
                // Xác định loại nấm ma được ăn
                int mush_type = int(s[i]) - 48;
                event_13(myHero, mush_type, file_mush_ghost);
            }
        }
        // Sự kiện 15
        else if (event[i] == 15)
        {
            if (myHero.remdedy < Max_remedy)
                myHero.remdedy++;
        }
        // Sự kiện 16
        else if (event[i] == 16)
        {
            if (myHero.maidenkiss < Max_maidenkiss)
                myHero.maidenkiss++;
        }
        // Sự kiện 17
        else if (event[i] == 17)
        {
            if (myHero.phoenixdown < Max_phoenixdown)
                myHero.phoenixdown++;
        }
        // Sự kiện 19
        else if (event[i] == 19)
        {
            event_19(myHero, file_asclepius_pack);
        }
        // Sự kiện 99
        else if (event[i] == 99)
        {
            event_99(myHero);
        }
        // Sự kiện 18
        else if (event[i] == 18)
        {
            event_18(myHero, file_merlin_pack);
        }
        // Kiểm tra xem hết bị tí hon chưa
        if (endTiny(myHero, i, checkevent_6_end, isTiny))
        {
            myHero.HP = (myHero.HP * 5 > myHero.max_HP) ? (myHero.max_HP) : (myHero.HP * 5);
            checkevent_6_end = -9999;
        }
        // Kiểm tra xem hết bị biến thành ếch chưa
        if ((isFrog) && (i - checkevent_7_end == 3))
        {
            myHero.level = prev_level;
        }
        // // Debug line
        // cout << "Sau index: " << i << " event: " << event[i] << " HP: " << myHero.HP << endl;
        // In ra thông tin hiệp sĩ sau mỗi sự kiện
        if (event[i + 1] == -1 && myHero.HP > 0)
        {
            myHero.rescue = 1;
        }
        update(myHero, HP, level, remedy, maidenkiss, phoenixdown, rescue);
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
    }
    filein.close();
}