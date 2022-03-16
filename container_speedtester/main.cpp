/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 08:58:14 by youssou          #+#    #+#             */
/*   Updated: 2021/12/01 21:19:01 by youssou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdexcept>

int main(int ac, char **av){
    char buffer[256];
    unsigned int index = 0, total = 0;;
    std::string ft_print[4], std_print[4], tested_name = "";
    std::string arg(av[1]);
    arg.append(" 2>&1 temp.txt");
    std::cout << arg.c_str() << "\n";
    FILE *pipe = popen(arg.c_str(), "r");
    std::cout << "\e[1;32mAll the tests are STD-Friendly, meaning that the STD do NOT segfault on the tests.\e[0m" << std::endl;
    std::cout << "\e[1;32mTester is not comparing output, only speed.\e[0m" << std::endl;
    if (!pipe) throw (std::runtime_error("popen() failed !"));
    try {
        while (fgets(buffer, sizeof(buffer), pipe) != NULL){
            if (index == 0)
                tested_name = buffer;
            if (index > 0 && index <= 4)
                ft_print[index - 1] = buffer;
            if (index >= 5)
                std_print[index - 5] = buffer;
            index++;
            if (index == 9){
                if (total == 0)
                    std::cout << std::endl << " "; 
                std::cout << tested_name;
                for (int y = 0; y < 4; y++){
                    ft_print[y].pop_back();
                    std_print[y].pop_back();
                    std::cout << ft_print[y];
                    if (y == 0)
                        std::cout << "          |  ";
                    else
                        std::cout << "   |   ";
                    std::cout << std_print[y] << std::endl << " ";
                }
                for (int i = 0; i < 4; i++){
                    ft_print[i] = "";
                    std_print[i] = "";
                }
                index = 0;
                std::cout << "\e[1;34m---------------------------------------\e[0m" << std::endl << " ";
                total++;
            }
            
        }
    }   catch (...){
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return (0);
}