/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    std::string file = file_to_string(filename);

    char c = '\n';
    std::vector<std::string> v;
    int h = split_string(file, c, v);
    
    c = ',';
    std::vector<std::string> v2;
    int num = split_string(file, c, v2);
    
    V2D ret;
    for(int i = 0; i < h; i++) {
        std::vector<std::string> v3;
        int tmp_size = split_string(v[i], ',', v3);
        for(int j = 0; j < tmp_size; j++) v3[j] = trim(v3[j]);
        std::vector<std::string> v4;
        for(unsigned k = 0; k < v3.size(); k++) v4.push_back(v3[k]);
        ret.push_back(v4);

        v3.clear();
        v4.clear();

    }

    
    /*std::vector<std::string> v4;
    for(int i = 0; i < num; i++) {
        std::vector<std::string> v5;
        split_string(v3[i], '\n', v5);
        for(size_t j = 0; j < v5.size(); j++) v4.push_back(v5[j]);

        v5.clear();
    }

    for(int i = 0; i < w*h; i++) v4[i] = trim(v4[i]);
    V2D ret(h, std::vector<std::string> (w));
    int x = 0;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            ret[i][j] = v4[x];
            x++;
        }
    }*/
    return ret;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    V2D ret;
    for(unsigned i = 0; i < cv.size(); i++) {
        std::vector<std::string> v;
        v.push_back(cv[i][0]);
        unsigned size = cv[i].size();
        for(unsigned j = 1; j < size; j++) {
            bool check = false;
            for(unsigned x = 0; x < student.size(); x++) {
                if(cv[i][j].compare(student[x][0]) == 0) {
                    for(unsigned a = 1; a < student[x].size(); a++) {
                        if(cv[i][0].compare(student[x][a]) == 0) {
                            check = true;
                        }
                    }
                }
            }
            if(check == true) {
                //std::cout << v[0][j] << " v before erase ";
                //v[0].erase(v[0].begin()+j);
                //std::cout << v[0][j] << " v after erase " << std::endl;
                //size--;
                //j--;
                v.push_back(cv[i][j]);
            }
            //std::cout << j << " j ";
        }
        //std::cout << std::endl;
        /*for(unsigned w = 0; w < v[0].size(); w++) std::cout << v[0][w] << " ";
        std::cout << std::endl;*/
        if(v.size() > 1) {
            ret.push_back(v);
        }
        v.clear();
    }
    //std::cout << " done!" << std::endl;
    return ret;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    unsigned num_courses = courses.size();
    // 0 means no vertex, 1 means vertex
    std::vector<std::vector<int>> adj_matrix(num_courses, std::vector<int>(num_courses));
    for(unsigned i = 0; i < num_courses; i++) {
        for(unsigned j = 0; j < num_courses; j++) {
            // start with no vertices
            adj_matrix[i][j] = 0;
        }
    }
    for(unsigned i = 0; i < num_courses; i++) {
        for(unsigned j = 1; j < courses[i].size(); j++) {
            for(unsigned x = 0; x < num_courses; x++) {
                if(i == x) continue;
                for(unsigned y = 1; y < courses[x].size(); y++) {
                    if(courses[i][j].compare(courses[x][y]) == 0) {
                        adj_matrix[i][x] = 1;
                        adj_matrix[x][i] = 1;
                    }
                }
            }
        }
    }
    // check if correctly populated
    /*for(unsigned i = 0; i < num_courses; i++) {
        for(unsigned j = 0; j < num_courses; j++) {
            std::cout << adj_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }*/
    // adj_matrix should be correctly populated by now
    // now time for coloring our graph
    std::vector<int> vertices(courses.size());
    // true means can be used and false means already taken by adj
    std::vector<bool> colors(timeslots.size());
    /*for(unsigned i = 0; i < timeslots.size(); i++) colors[i] = true;
    for(unsigned i = 1; i < courses.size(); i++) vertices[i] = -1;*/

    // go through all starting points
    for(unsigned a = 0; a < courses.size(); a++) {
        // set up check bool, starting point, and our two vectors for coloring
        std::cout << " a: " << a;
        bool did_it_work = true;
        vertices[a] = 0;
        for(unsigned i = 0; i < timeslots.size(); i++) colors[i] = true;
        for(unsigned i = 0; i < courses.size(); i++) {
            if(a == i) continue;
            vertices[i] = -1;
        }
        // color time
        for(unsigned i = 0; i < courses.size(); i++) {
            // if same vertice ignore
            if(a == i) continue;
            // set up which colors aren't possible
            for(unsigned j = 0; j < courses.size(); j++) {
                if(adj_matrix[i][j] == 1 && vertices[j] != -1) {
                    colors[vertices[j]] = false;
                }
            }
            // find the first color that works
            unsigned c = 0;
            for(c = 0; c < timeslots.size(); c++) {
                if(colors[c]) break;
            }
            // if no color this starting point doesn't work
            if(c >= timeslots.size()) {
                did_it_work = false;
                break;
            }
            vertices[i] = c;
            for(unsigned j = 0; j < timeslots.size(); j++) colors[j] = true;
        }
        // if last starting point doesn't work return the bad V2D
        if(a + 1 == num_courses && did_it_work == false) {
            V2D ret_bad;
            std::vector<std::string> ret_v;
            ret_v.push_back("-1");
            ret_bad.push_back(ret_v);
            return ret_bad;
        }
        // if did work break out of trying
        if(did_it_work) break;
    }
    std::cout << std::endl;
    // set up return V2D!
    V2D ret;
    for(unsigned i = 0; i < timeslots.size(); i++) {
        std::vector<std::string> times;
        times.push_back(timeslots[i]);
        ret.push_back(times);
        times.clear();
    }
    for(unsigned i = 0; i < vertices.size(); i++) {
        ret[vertices[i]].push_back(courses[i][0]);
    }
    return ret;
}