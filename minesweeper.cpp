#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include "clui.h"
#define max_string_length 200 
#define leaderboard_top_players_number 5 
#define max_users_number 10
#define bombs_coordinates_Size_max 96
#define map_Size_max 20
using namespace std ;
struct user{
    //char name[max_string_length] ;
    char name[max_string_length] ;
    int score ;
} ;
int map[map_Size_max][map_Size_max], bombs_i_coordinates[bombs_coordinates_Size_max],   bombs_j_coordinates[bombs_coordinates_Size_max] ;
char user_map[map_Size_max][map_Size_max] ;
int map_Size = 5, bombs_coordinates_Size = 4 ;
int len(char* s){
    int i = 0 ;
    while(s[i] != '\0'){
        i++ ;
    }
    return i ;
}
void copy_str(char* str1, char* str2){
    for (int i = 0 ; i < len(str1) ; i++){
        str2[i] = str1[i] ;
    }
}
bool is_yeksan_reshte(char* str1, char* str2){
    if (len(str1)!= len(str2)){
        return false ;
    }
    for (int i = 0 ; i < len(str1) ; i++){
        if (str1[i]!= str2[i]){
            return false ;
        }
    }
    return true ;
}

int random_bomb_coordinate_generator(int number){ //returns random numb in range [0, number-1]
    return (rand() % number) ;
}
// we'll need 2 random numbers to put our bombs into the game map
bool is_new_bomb(int bombs_i_coordinates[], int bombs_j_coordinates[], int i, int j){
    for (int k = 0 ; k < bombs_coordinates_Size ; k++){
        if (i == bombs_i_coordinates[k] && j == bombs_j_coordinates[k]){
                return false ;
        }
    }
    return true ;
}
bool out_of_bound(int i, int j, int size){ //to control out of index errors in arrays
    if ((i >= 0 && i < size) && (j>=0 && j < size)){
        return true ;
    }
    return false ;
}
void bomb_maker(int bombs_i_coordinates[], int bombs_j_coordinates[]){
    int bomb_i, bomb_j ;
    bool are_all_bombs_made = false ;
    int bomb_counter = 0 ;
    for (int k = 0 ; k < bombs_coordinates_Size ; k++){ 
        bombs_i_coordinates[k] = -10 ;
        bombs_j_coordinates[k] = -10 ;
    }
    // we put -10 so then we can check if there has been a bomb there or not before, with coordinates in range[0,5]
    while (!are_all_bombs_made){
        bomb_i = random_bomb_coordinate_generator(map_Size) ;
        bomb_j = random_bomb_coordinate_generator(map_Size) ;
        if(is_new_bomb(bombs_i_coordinates, bombs_j_coordinates, bomb_i, bomb_j)){
            bombs_i_coordinates[bomb_counter] = bomb_i ;
            bombs_j_coordinates[bomb_counter] = bomb_j ;
            bomb_counter++ ;
        }
        if (bomb_counter == bombs_coordinates_Size){
            are_all_bombs_made = true ;
        }
    }
}
void map_generator(int bombs_i_coordinates[], int bombs_j_coordinates[]){
    for (int i = 0 ; i < map_Size ; i++){
        for (int j = 0 ; j < map_Size ; j++){
            map[i][j] = 0 ;
        }
    }
    for (int i = 0 ; i < bombs_coordinates_Size ; i++){
        map[bombs_i_coordinates[i]][bombs_j_coordinates[i]] = -1 ; //bombs are shown with -1 in the map
    }
    for (int i = 0 ; i < map_Size ; i++){
        for (int j = 0 ; j < map_Size ; j++){
            if (map[i][j] != -1){
                int output = 0 ;
                if (out_of_bound(i-1, j-1, map_Size)){
                    if(map[i-1][j-1] == -1){
                        output++ ;
                    }
                }
                if (out_of_bound(i-1, j, map_Size)){
                    if(map[i-1][j] == -1){
                        output++ ;
                    }
                }
                if (out_of_bound(i-1, j+1, map_Size)){
                    if(map[i-1][j+1] == -1){
                        output++ ;
                    }
                }
                if (out_of_bound(i, j-1, map_Size)){
                    if(map[i][j-1] == -1){
                        output++ ;
                    }
                }
                if (out_of_bound(i, j+1, map_Size)){
                    if(map[i][j+1] == -1){
                        output++ ;
                    }
                }
                if (out_of_bound(i+1, j-1, map_Size)){
                    if(map[i+1][j-1] == -1){
                        output++ ;
                    }
                }
                if (out_of_bound(i+1, j, map_Size)){
                    if(map[i+1][j] == -1){
                        output++ ;
                    }
                }
                if (out_of_bound(i+1, j+1, map_Size)){
                    if(map[i+1][j+1] == -1){
                        output++ ;
                    }     
                } 
                map[i][j] = output ;         
            }
        }
    }
}
void show_main_map(bool win){
    for (int i = 0 ; i < map_Size ; i++){ //The real map with all indexes
        for (int j = 0 ; j < map_Size ; j++){
            delay(50) ;
            if(map[i][j] == -1){
                cout << "B" << " "; // B stands for bombs!
            }
            else{
                cout << map[i][j] << " " ;
            }
            
        }
    cout << endl ;
    }
    if (win){
        save_cursor() ;
        int cols =  get_window_cols();
        int middle = cols / 2;
        cursor_to_pos(0, middle);    
        cout << "\\(^o^)/" << endl ; //when the user wins!                     
    }
}
//Now lets play with the user :)
bool is_wrong_char_input(char expected, char input){ //checks if the input given matches the expected one
    if (expected == input){ //esc is ok
        return false ;
    }
    else if (input != 27){
        return true ;
    }
    return true ; //to avoid no_return errors
}
bool is_wrong_int_input(int expected_range, int input){ //checks if the input is in range[0, expected_range)
    if (input < expected_range && input >= 0){
        return false ;
    }
    return true ;
}
void bye(){
    change_color_rgb(169, 191, 6) ; // 0 color
    cout <<"BYE!" ;
    reset_color() ;    
}
bool is_escape(char input){//the user can exit the game whenever wanted to
    if (input == 27){ //ESC ASCII is 27
        return true ;
    }
    return false ;
}
bool is_save_and_quit(char input){
    if (input == 'o' || input == 'O'){ 
        return true ;
    }
    return false ;
}

bool keyboard_or_coordinate(bool &Game_On){
    change_color_rgb(52, 235, 91) ; //we'll always talk like this
    cout << "Choose to play with keyboard(Press K) or to play with number-coordinates(Press N)" << endl ;
    char input = getch() ;
    Game_On = !is_escape(input) ;
    while ((is_wrong_char_input('K', input) && is_wrong_char_input('k', input)) && (is_wrong_char_input('N', input) && is_wrong_char_input('n', input)) && Game_On){
        change_color_rgb(214, 48, 6) ; //error color
        cout << "Please enter the correct form needed" << endl ;
        delay(1500) ;
        clear_screen() ;
        change_color_rgb(52, 235, 91) ;
        cout << "Choose to play with keyboard(Press K) or to play with number-coordinates(Press N)" << endl ;
        input = getch() ;
        Game_On = !is_escape(input) ;
    }
    reset_color() ;
    if (input == 'K' || input == 'k'){
        return true ;
    }
    return false ;
}
bool out_of_bound_keyboard_edition(int i, int j){
    if ((i>=0 && i <= map_Size) && (j>=0 && j<map_Size*2)){
        return true ;
    }
    return false ;
}
void save_game() ;
bool is_winner() ;
void keyboard(int &i, int &j, bool &Game_On){
    change_color_rgb(52, 235, 91) ; //we'll always talk like this
    cout << "You can move with arrow keys, click Enter when you're done with moving" << endl ;
    char key = getch() ;
    Game_On = !is_escape(key) ;
    bool lets_save = is_save_and_quit(key) ;
    if (lets_save){
        save_game() ;
    }
    Game_On = !lets_save && !is_escape(key) ;
    int i_backup = 0, j_backup = 0 ;
    while(key != 13 && Game_On){ //13 is Enters ascii code
        i_backup = i ;
        j_backup = j ;
        switch(key){
            case 72: //up
                i-- ;
                break;
            case 80: //down
                i++ ;  
                break;
            case 77: //right
                j++ ;
                break;
            case 75: //left
                j-- ;
                break;
        }  
        if (out_of_bound_keyboard_edition(i, j)){
            cursor_to_pos(i, j);
        }
        else{
            i = i_backup ;
            j = j_backup ;
        }
        cursor_to_pos(i, j);
        key = getch() ;
        //Game_On = is_escape(key) ;
        lets_save = is_save_and_quit(key) ;
        if (lets_save){
            save_game() ;
        }
        Game_On = !lets_save && !is_escape(key) ;
    }   
    cursor_to_pos(map_Size + 2, 0) ;
    i_backup = i ;
    j_backup = j ;    
    i-- ;
    j = j / 2 ;  
    if (!out_of_bound_keyboard_edition(i, j)){
            i++ ;
    }   
    reset_color() ;     
}
void user_map_generator(){
    for (int i = 0 ; i < map_Size ; i++){
        for (int j = 0 ; j < map_Size ; j++){
            user_map[i][j] = 'X' ;
        }
    }
}
void user_map_update(int i, int j, bool what, int &flag_counter, bool Game_On){
    if (Game_On){ 
        if(what){
            if (user_map[i][j] == 'F'){
                change_color_rgb(214, 48, 6) ; //error color  
                cout << "You cant select a previously flagged point, first you need to pick up the flag" << endl ;
                delay(3000) ;
                what = true ; //to turn flag_or_check into false so then the bomb doesnt explode
            }
            else{
                if (map[i][j] == 0 && user_map[i][j]!= '0'){
                    user_map[i][j] = char(map[i][j] + int ('0')) ;
                    int fake_0 = 0;
                    if (out_of_bound(i-1, j-1, map_Size)){
                        user_map_update(i-1, j-1, true, fake_0, true) ; //the last 3 function datas are given cause we know theres no bomb in neighbours houses
                        clear_screen() ;
                    }
                    if (out_of_bound(i-1, j, map_Size)){
                        user_map_update(i-1, j, true, fake_0, true) ;
                        clear_screen() ;
                    }
                    if (out_of_bound(i-1, j+1, map_Size)){
                        user_map_update(i-1, j+1, true, fake_0, true) ;
                        clear_screen() ;
                    }
                    if (out_of_bound(i, j-1, map_Size)){
                        user_map_update(i, j-1, true, fake_0, true) ;
                        clear_screen() ;
                    }
                    if (out_of_bound(i, j+1, map_Size)){
                        user_map_update(i, j+1, true, fake_0, true) ;
                        clear_screen() ;
                    }
                    if (out_of_bound(i+1, j-1, map_Size)){
                        user_map_update(i+1, j-1, true, fake_0, true) ;
                        clear_screen() ;
                    }
                    if (out_of_bound(i+1, j, map_Size)){
                        user_map_update(i+1, j, true, fake_0, true) ;
                        clear_screen() ;
                    }
                    if (out_of_bound(i+1, j+1, map_Size)){
                        user_map_update(i+1, j+1, true, fake_0, true);
                        clear_screen() ;    
                    } 
                }
                user_map[i][j] = char(map[i][j] + int ('0')) ;
                change_color_rgb(6, 185, 191) ; // 1 color
                cout << "Selected! " << endl ;            
            }        
        }
        else if (user_map[i][j] == 'F'){
            user_map[i][j] = 'X' ;
            flag_counter-- ;
            change_color_rgb(6, 185, 191) ; // 1 color
            cout << "Flag picked up!" << endl ;
        }
        else{
            if (flag_counter == bombs_coordinates_Size){
                change_color_rgb(214, 48, 6) ; //error color
                cout << "You cant place more than " << bombs_coordinates_Size << " flags, first you need to pick up a previously placed flag" << endl ;
                delay(3000) ;
            }
            else{
                user_map[i][j] = 'F' ;
                flag_counter++ ;    
                change_color_rgb(6, 185, 191) ; // 1 color
                cout << "Flag placed! " << endl ;
            }
        }  
        reset_color() ; 
    }       
}
void point_color(int i, int j){
    if(user_map[i][j] == '0'){
        change_color_rgb(169, 191, 6) ; // 0 color
        //map[i][j] = ' ' ; //remember to fix
    }
    if(user_map[i][j] == '1'){
        change_color_rgb(6, 185, 191) ; // 1 color
    }
    if(user_map[i][j] == '2'){
        change_color_rgb(191, 6, 126) ; // 2 color
    }
    if(user_map[i][j] == '3'){
        change_color_rgb(6, 166, 0) ; // 3 color
    }   
    if(user_map[i][j] == '4'){
        change_color_rgb(255, 0, 238) ; // 4 color
    } 
    if(user_map[i][j] == '5'){
        change_color_rgb(8, 23, 212) ; // 5 color
    }       
    if(user_map[i][j] == '6'){
        change_color_rgb(130, 3, 3) ; // 6 color
    }               
}

void show_map(){
    for (int i = 0 ; i < map_Size ; i++){
        for (int j = 0 ; j < map_Size ; j++){
            point_color(i, j) ;
            cout << user_map[i][j] << " " ;
            reset_color() ;
            delay(50) ;
        }
        cout << endl ;
    }
}

void get_user_coordinates(int &i, int &j, bool &Game_On){
    if (Game_On){
        change_color_rgb(52, 235, 91) ; //we'll always talk like this
        cout << "Enter the i, j coordinates (in range 0 to " << map_Size - 1 << ") which you want to use in the map" << endl ;
        i = getch() - int('0') ; // cause getch gets the char form
        j = getch() - int('0') ;
        Game_On = !is_escape(char(i + int('0'))) && !is_escape(char(j + int ('0'))) ; 
        while ((is_wrong_int_input(map_Size, i) || is_wrong_int_input(map_Size, j)) && Game_On){
            change_color_rgb(214, 48, 6) ; //error color
            cout << "Please enter the correct form needed, like " << map_Size-1 << " " << 0 << endl ;
            change_color_rgb(52, 235, 91) ; //we'll always talk like this
            cout << "Enter the i, j coordinates (in range 0 to " << map_Size - 1 << ") which you want to use in the map" << endl ;
            i = getch() - int('0') ; // cause getch gets the char form
            j = getch() - int('0') ;
            Game_On = !is_escape(char(i + int('0'))) ;
            Game_On = !is_escape(char(j + int ('0'))) ;
        }
        reset_color() ;
    }
}
bool what_to_do(bool &Game_On){ // true stands for selecting and false stands for puting a flag
    if (Game_On){ 
        change_color_rgb(52, 235, 91) ; //we'll always talk like this
        cout << "Choose to select a point with S or you can put/pick up a flag there with F!" << endl ;
        char select_or_flag = getch() ;
        Game_On = !is_escape(select_or_flag) ;
        while(is_wrong_char_input('f', select_or_flag) && is_wrong_char_input('F', select_or_flag) && is_wrong_char_input('S', select_or_flag) && is_wrong_char_input('s', select_or_flag) && Game_On){
            change_color_rgb(214, 48, 6) ; //error color
            cout << "Please enter the correct form needed" << endl ;
            change_color_rgb(52, 235, 91) ; //we'll always talk like this
            cout << "Choose to check a point with S or you can put/pick up a flag there with F!" << endl ;
            select_or_flag = getch() ;
            Game_On = !is_escape(select_or_flag) ;
        }
        reset_color() ;
        if (select_or_flag == 'f' || select_or_flag == 'F'){
            return false ;
        }
        else{
            return true ; 
        }
    }
    return true ;
}        
bool bomb_explode(int bombs_i_coordinates[], int bombs_j_coordinates[], int i, int j){
    for (int k = 0 ; k < bombs_coordinates_Size ; k++){
        if (i == bombs_i_coordinates[k] && j == bombs_j_coordinates[k]){
                return true ;
        }
    }
    return false ;
}
void game_over(){
    change_color_rgb(186, 0, 0) ;
    cout << "Game " ;
    delay(500) ;
    cout<< "Over " ;
    delay(500) ;
    cout << " !!!"<< endl ;
    delay(500) ;
    reset_color() ;
}
bool is_winner(){
    for (int i = 0 ; i < map_Size ; i++){
        for (int j = 0 ; j < map_Size ; j++){
            if (map[i][j] != -1 && user_map[i][j] == 'X'){
                return false ;
            }
        }
    }
    return true ;
}
void win(){
    change_color_rgb(6, 199, 164) ; 
    cout << "You " ;
    delay(500) ;
    cout<< "Won " ;
    delay(500) ;
    cout << "!!!" << endl ;
    reset_color() ;
}
int score_compute(){
    int unlocked_places = 0 ;
    for (int i = 0 ; i < map_Size ; i++){
        for (int j = 0 ; j < map_Size ; j++){
            if (user_map[i][j] != 'X' && user_map[i][j] != 'F'){
                unlocked_places++ ;
            }
        }
    }
    return (10 * unlocked_places * (bombs_coordinates_Size / 4) * (map_Size * map_Size / (5 * 5))) ; //score formula computation - 4 min bombs and 5 min map size
}
void export_data_from_leaderboard_txt(user* leaderboard, int &counter){
    ifstream leaderboard_names("leaderboard_Names.txt") ;
    ifstream leaderboard_scores("leaderboard_Scores.txt") ; 
    int data_lines = 0 ;
    leaderboard_scores >> data_lines ;
    counter = data_lines ;
    for (int i = 0 ; i < data_lines ; i++){
        leaderboard_names.getline(leaderboard[i].name, max_string_length) ;
        leaderboard_scores >> leaderboard[i].score ;
    }
    leaderboard_names.close() ;
    leaderboard_scores.close() ;
}
void insert_data_to_leaderboard_txt(user* leaderboard, int data_lines){
    ofstream leaderboard_names("leaderboard_Names.txt") ;
    ofstream leaderboard_scores("leaderboard_Scores.txt") ; 
    leaderboard_scores << data_lines << endl ;
    for (int i = 0 ; i < data_lines ; i++){
        leaderboard_names << leaderboard[i].name << endl ;
        leaderboard_scores << leaderboard[i].score << endl ;
    } 
    leaderboard_names.close() ;   
    leaderboard_scores.close() ;    
}
void sort_leaderboard(user* leaderboard, int data_lines){
    for (int i = 0 ; i < data_lines -1  ; i++){//bubble sort for names&scores
        for (int j = 0 ; j < data_lines -i -1 ; j++){
            if (leaderboard[j].score < leaderboard[j+1].score){
                user temp = leaderboard[j] ;
                leaderboard[j] = leaderboard[j+1] ;
                leaderboard[j+1] = temp ;
            }
        }
    }  
}
int search_for_old_players(user* leaderboard, int data_lines, char* new_user){
    for (int i = 0 ; i < data_lines ; i++){
        if (is_yeksan_reshte(new_user, leaderboard[i].name)){
            return i ;
        }
    }
    return -1 ; // means that this one is a new user!
}
void show_top_players_leaderboard(user leaderboard[], int data_lines){
    clear_screen() ;
    change_color_rgb(4, 214, 147) ;  //top players color
    int repeat = leaderboard_top_players_number ; 
    if (data_lines < repeat){
        repeat = data_lines ;
    }
    for (int i = 0 ; i < repeat ; i++){
        cout << leaderboard[i].name << " | " << leaderboard[i].score << endl ;
    }
    delay(5000) ;
    //press esc to go back to menu
    reset_color() ;
}

////Save and load game
void save_game(){
    clear_screen() ;
    ifstream save_slots("SaveSlotNames.txt") ;
    char* reader = new char[max_string_length] ;
    change_color_rgb(6, 185, 191) ; // 1 color
    for (int i = 0 ; i < 4 ; i++){ //cause there are four save slots
        save_slots >> reader ;
        cout << i + 1 << " |" << reader << endl ;
    }
    save_slots.close() ;
    delete[] reader ;
    change_color_rgb(52, 235, 91) ; //we'll always talk like this
    cout << "choose the slot's number you would like to save the game into" << endl ;
    char chosen_slot = getch() ;
    switch(chosen_slot){
        case '1' :
        {
            ofstream saved_user_map("Slot1_user.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_user_map << user_map[i][j] ;
                }
                saved_user_map << endl ;
            }
            saved_user_map.close() ;
            break ; 
        }                   

        case '2' :
        {
            ofstream saved_user_map("Slot2_user.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_user_map << user_map[i][j] ;
                }
                saved_user_map << endl ;
            }
            saved_user_map.close() ;
            break ; 
        }
        case '3' :
        {
            ofstream saved_user_map("Slot3_user.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_user_map << user_map[i][j] ;
                }
                saved_user_map << endl ;
            }
            saved_user_map.close() ;
            break ; 
        }
        case '4' :
        {
            ofstream saved_user_map("Slot4_user.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_user_map << user_map[i][j] ;
                }
                saved_user_map << endl ;
            }
            saved_user_map.close() ;
            break ; 
        }
        default :
        {
            change_color_rgb(214, 48, 6) ; //error color
            cout << "Please enter in the correct form asked" << endl ;
            delay(2000) ;
            save_game() ;     
        }                                   
    }
    switch(chosen_slot){
        case '1' :
        {
            ofstream saved_main_map("Slot1_main.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    if (map[i][j] == -1){
                        map[i][j] = 9 ; //9 is impossible so its a code for bombs
                    }
                    saved_main_map << map[i][j] ;
                }
                saved_main_map << endl ;
            }
            saved_main_map.close() ; 
            break ;
        }            
        case '2' :
        {
            ofstream saved_main_map("Slot2_main.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    if (map[i][j] == -1){
                        map[i][j] = 9 ; //9 is impossible so its a code for bombs
                    }                    
                    saved_main_map << map[i][j] ;
                }
                saved_main_map << endl ;
            }
            saved_main_map.close() ; 
            break ;
        }
        case '3' :
        {
            ofstream saved_main_map("Slot3_main.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    if (map[i][j] == -1){
                        map[i][j] = 9 ; //9 is impossible so its a code for bombs
                    }                    
                    saved_main_map << map[i][j] ;
                }
                saved_main_map << endl ;
            }
            saved_main_map.close() ; 
            break ;
        }
        case '4' :
        {
            ofstream saved_main_map("Slot4_main.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    if (map[i][j] == -1){
                        map[i][j] = 9 ; //9 is impossible so its a code for bombs
                    }                    
                    saved_main_map << map[i][j] ;
                }
                saved_main_map << endl ;
            }
            saved_main_map.close() ; 
            break ;
        }                                   
    } 
    change_color_rgb(255, 0, 238) ; // 4 color
    cout << "Saved Completely =) " << endl ;
    delay(2000) ;
    reset_color() ;
}
void load_game(){
    clear_screen() ;
    ifstream save_slots("SaveSlotNames.txt") ;
    char* reader = new char[max_string_length] ;
    change_color_rgb(6, 185, 191) ; // 1 color
    for (int i = 0 ; i < 4 ; i++){ //cause there are four save slots
        save_slots >> reader ;
        cout << i + 1 << " |" << reader << endl ;
    }
    save_slots.close() ;
    delete[] reader ;
    change_color_rgb(52, 235, 91) ; //we'll always talk like this
    cout << "choose the slot's number you would like to load the game into" << endl ;
    char chosen_slot = getch() ;
    switch(chosen_slot){
        case '1' :
        {
            ifstream saved_user_map("Slot1_user.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_user_map >> user_map[i][j] ;
                }
            }
            saved_user_map.close() ;
            break ; 
        }                   

        case '2' :
        {
            ifstream saved_user_map("Slot2_user.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_user_map >> user_map[i][j] ;
                }
            }
            saved_user_map.close() ;
            break ; 
        }
        case '3' :
        {
            ifstream saved_user_map("Slot3_user.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_user_map >> user_map[i][j] ;
                }
            }
            saved_user_map.close() ;
            break ; 
        }
        case '4' :
        {
            ifstream saved_user_map("Slot4_user.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_user_map >> user_map[i][j] ;
                }
            }
            saved_user_map.close() ;
            break ; 
        }
        default :
        {
            change_color_rgb(214, 48, 6) ; //error color
            cout << "Please enter in the correct form asked" << endl ;
            delay(2000) ;
            load_game() ;     
        }                                   
    }
    int bombs_list_counter = 0 ;
    switch(chosen_slot){
        char k ;
        
        case '1' :
        {
            ifstream saved_main_map("Slot1_main.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_main_map >> k ;
                    if (k == '9'){ //bombs are saved with 9 in txt file, but -1 in map 
                        map[i][j] = -1 ;
                        bombs_i_coordinates[bombs_list_counter] = i ;
                        bombs_j_coordinates[bombs_list_counter] = j ;
                        bombs_list_counter++ ;
                    }
                    else{
                        map[i][j] = int (k - '0') ;
                    }
                    
                }
            }
            saved_main_map.close() ; 
            break ;
        }            
        case '2' :
        {
            ifstream saved_main_map("Slot2_main.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_main_map >> k ;
                    if (k == '9'){ //bombs are saved with 9 in txt file, but -1 in map 
                        map[i][j] = -1 ;
                        bombs_i_coordinates[bombs_list_counter] = i ;
                        bombs_j_coordinates[bombs_list_counter] = j;
                        bombs_list_counter++ ;
                    }
                    else{
                        map[i][j] = int (k - '0') ;
                    }
                }
            }
            saved_main_map.close() ; 
            break ;
        }
        case '3' :
        {
            ifstream saved_main_map("Slot3_main.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_main_map >> k ;
                    if (k == '9'){ //bombs are saved with 9 in txt file, but -1 in map 
                        map[i][j] = -1 ;
                        bombs_i_coordinates[bombs_list_counter] = i ;
                        bombs_j_coordinates[bombs_list_counter] = j ;
                        bombs_list_counter++ ;
                    }
                    else{
                        map[i][j] = int (k - '0') ;
                    }
                }
            }
            saved_main_map.close() ; 
            break ;
        }
        case '4' :
        {
            ifstream saved_main_map("Slot4_main.txt") ;
            for (int i = 0 ; i < map_Size ; i++){
                for (int j = 0 ; j < map_Size ; j++){
                    saved_main_map >> k ;
                    if (k == '9'){ //bombs are saved with 9 in txt file, but -1 in map 
                        map[i][j] = -1 ;
                        bombs_i_coordinates[bombs_list_counter] = i ;
                        bombs_j_coordinates[bombs_list_counter] = j ;
                        bombs_list_counter++ ;
                    }
                    else{
                        map[i][j] = int (k - '0') ;
                    }
                }
            }
            saved_main_map.close() ; 
            break ;
        }                                   
    } 
    change_color_rgb(255, 0, 238) ; // 4 color
    cout << "Saved Game loaded Completely =) " << endl ;
    delay(2000) ;
    reset_color() ;           
}
void level(){
    change_color_rgb(52, 235, 91) ; //we'll always talk like this
    cout << "1 |Easy" << endl ;
    cout << "2 |Casual" << endl ;
    cout << "3 |Hard" << endl ;
    cout << "4 |Custom" << endl ;
    cout << "Enter the level number you want to play" << endl ;
    char input ;
    input = getch() ;
    if(input == '1'){
        return ;
    }
    else if (input == '2'){
        map_Size = 12 ;
        bombs_coordinates_Size = 28 ;
    }
    else if (input == '3'){
        map_Size = 20 ;
        bombs_coordinates_Size = 96 ;
    }
    else if (input == '4') {
        cout << "Enter map size in range[5 - 20]" << endl ;
        int int_input ;
        cin >> int_input ;
        while (!(int_input >= 5 && int_input <= 20)){
            change_color_rgb(214, 48, 6) ; //error color
            cout << "Please enter in the correct form asked" << endl ;
            change_color_rgb(52, 235, 91) ; //we'll always talk like this
            cout << "Enter map size in range[5 - 20]" << endl ;
            cin >> int_input ;
        }
        map_Size = int_input ;
        cout << "Enter bombs number in range[5 - 20]" << endl ;
        cin >> int_input ;
        bombs_coordinates_Size = int_input ;
    }
    else{
        change_color_rgb(214, 48, 6) ; //error color
        cout << "Please enter in the correct form asked" << endl ;
        delay(2000) ;
        level() ;        
    }
    reset_color() ;
}
void new_game(){
    clear_screen() ;
    level() ;
    reset_color() ;
    // game on true
}
void show_menu(){
    change_color_rgb(52, 235, 91) ; //we'll always talk like this
    cout << "1 |New Game" << endl ;
    cout << "2 |Load Game" << endl ;
    cout << "3 |Change Name" << endl ;
    cout << "4 |Leaderboard" << endl ;
    cout << "5 |Quit" << endl ;
    cout << "Choose what would you like to do with arrow keys or enter the number!" << endl ;
    reset_color() ;
}
void change_name(char* changed_name){ 
    change_color_rgb(52, 235, 91) ; //we'll always talk like this
    cout << "Please type your name and press Enter!" << endl ;
    cin >> changed_name ;
    reset_color() ; 
    clear_screen() ;
}
void whats_gonna_happen(bool &Game_On, bool &Menu_On, bool &is_load, bool &is_change, char* changed_name, user* players, int data_lines){
    char input = getch() ;
    switch(input){
        case '1' :
            Game_On = true ;
            new_game() ;    
            break ;
        case '2' :
            Game_On = true ;
            is_load = true ;
            load_game() ;
            break ;
        case '3' :
            change_name(changed_name) ;
            is_change = true ;
            //show_menu() ;
            //whats_gonna_happen(Game_On, Menu_On, player, is_load, is_change, changed_name, players, data_lines) ;
            break ;
        case '4' :
            show_top_players_leaderboard(players, data_lines) ;
            break ;
        case '5' :
            bye() ;
            Menu_On = false ;
            Game_On = false ;
            break ;        
    }
}
int main(){
    init_clui();
    srand(time(NULL)) ;
    bool Menu_On = true, first_player = true  ;
    user* all_players = new user[10] ;
    char input[max_string_length] ;
    int player_counter = 0, index = 0 ;
    export_data_from_leaderboard_txt(all_players, player_counter) ;
    delay(2000) ;
    change_color_rgb(52, 235, 91) ; //we'll always talk like this
    cout << "Please type your name and press Enter!" << endl ;
    //cin >> player.name ;
    //player.score = 0 ;
    cin >> input ;
    if (search_for_old_players(all_players,player_counter,input) == -1){
        copy_str(input, all_players[player_counter].name) ;
        all_players[player_counter].score = 0 ;
        player_counter++ ;
    }
    reset_color() ;    
    while(Menu_On){
        clear_screen() ;
        show_menu() ;
        //int map[map_Size][map_Size], bombs_i_coordinates[bombs_coordinates_Size], bombs_j_coordinates[bombs_coordinates_Size] ;
        bool Game_On = false,  is_load = false, is_change = false, we_played = false ;
        char changed_name[max_string_length], player1[max_string_length] ;
        if (first_player){
            copy_str(input, player1) ;
        }
        //char user_map[map_Size][map_Size] ;
        whats_gonna_happen(Game_On, Menu_On, is_load, is_change,changed_name, all_players, player_counter) ;
        if(!is_load){
            bomb_maker(bombs_i_coordinates, bombs_j_coordinates) ;
            map_generator(bombs_i_coordinates, bombs_j_coordinates) ;
            user_map_generator() ;
        }
        //show_main_map(true) ;
        //delay(600) ;
        int flag_counter = 0 ;
        int i = 0 , j =0 ;
        while (Game_On && Menu_On){ 
            we_played = true ;   
            clear_screen() ;
            show_map() ;
            save_cursor();
            delay(1000) ; 
            bool flag_or_check, win_or_lost = is_winner() ; ;
            if(!win_or_lost){
                keyboard(i, j, Game_On) ; 
                flag_or_check = what_to_do(Game_On) ;
                user_map_update(i, j, flag_or_check, flag_counter, Game_On) ;   
            }
            //keyboard(i, j, Game_On) ;   
            //cout << "heres :" << i << " " << j << endl ;
            //bool win_or_lost = is_winner() ;
            
            if (bomb_explode(bombs_i_coordinates, bombs_j_coordinates, i, j) && flag_or_check && Game_On){
                clear_screen() ;
                game_over() ;
                Game_On = false ;
                show_main_map(win_or_lost) ;
                delay(5000) ;
                break ;
            }
            delay(1000) ;
            if (win_or_lost && Game_On){
                clear_screen() ;
                win() ;
                Game_On = false ;
                show_main_map(win_or_lost) ; 
                delay(5000) ;
                break ;
            }
        }
        if (we_played){
            //player.score += score_compute() ;
            //cout << "score :" << player.score << endl ;
            index = search_for_old_players(all_players, player_counter, player1) ;
            all_players[index].score += score_compute() ;
        }
        if(is_change){
            first_player = false ;
            //copy_str(changed_name, player.name) ;
            //player.score = 0 ;
            copy_str(changed_name, all_players[player_counter].name) ;
            copy_str(changed_name, player1) ;
            all_players[player_counter].score = 0 ;
            if (search_for_old_players(all_players,player_counter,player1) == -1){
                player_counter++ ;
            }
            delay(5000) ;
        }  
        sort_leaderboard(all_players, player_counter) ;      
    }
    insert_data_to_leaderboard_txt(all_players, player_counter) ;
    delete[] all_players ; 
    return 0 ;
} 
