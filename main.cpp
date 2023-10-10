/*!
  @file  main.cpp
  @brief main program file
*/
#include <iostream>
#include <vector>
#include <list>
#include <type_traits>
#include <string>
#include <tuple>
#include <fstream>

using namespace std;

/*
template <typename T>
struct is_container{
  template<typename U>
  static constexpr bool test(typename U::iterator*){return true;}
  template<typename U>
  static constexpr bool test(...){return false;}
  static constexpr bool value=test<T>(nullptr);
};
*/

                    
//*
template <typename T, typename = void>
struct is_container : std::false_type {};

//to exclude std::string from being container:
template <>
struct is_container<std::string> : std::false_type {};

template <typename T>
struct is_container<T, std::void_t<
                         typename T::value_type,
                         typename T::size_type,
                         typename T::allocator_type,
                         typename T::iterator,
                         typename T::const_iterator,
                         decltype(std::declval<T>().size()),
                         decltype(std::declval<T>().begin()),
                         decltype(std::declval<T>().end()),
                         decltype(std::declval<T>().cbegin()),
                         decltype(std::declval<T>().cend())
                         >> : std::true_type {};
//*/                         

/*
//does not work for std::tuple, because it doesn't have value_type field:
template <typename T>
struct is_vector{
  static constexpr bool value=std::is_same<T, std::vector<typename T::value_type, typename T::allocator_type>>::value;
};
*/



/*!
 * @brief Function1
 * @details random useless function
 * Formula: \f$ \sqrt{1}\f$ 
 * @param[in] x parameter #1
 * @return returns 1
 */
int func(int x){return 1;}

/*!
 * @brief   SFINAE integer
 * @details integer SFINAE print_ip function overload
 * @param[in] num integer variable that is expected to be converted to string
 * @tparam T signed integer variable type
 * @return void
 */
template <class T>
typename std::enable_if<std::is_signed<T>::value, void>::type
print_ip(T num)
{
  //cout<<"#1#"<<endl;
  const int bytes=sizeof(num);
  for(int i=bytes-1; i>=0; --i)
  {
    int base=128;
    int sum=0;
    
    for(int j=7; j>=0; --j)
    {
      int shift=i*8+j;
      sum += ((num>>shift)&1)*base;
      base/=2;
    }
    cout<<sum;
    if(i) cout<<".";
  }
  cout<<endl;
  //cout<<"bytes="<<bytes<<endl; 
  return;
  //
  const int size=sizeof(num);
  const int bits=size*8;
  int sum=0;
  int count=0;
  long long int base=1<<(8-1);
  for(int i=bits-1; i>=0; --i){
    unsigned int x=num>>i;
    //cout<<"i="<<i<<" x="<<( a>>i & 1)<<endl;
    sum += ( num>>i & 1) * base;
    base/=2;
    count++;
    if(count%8==0){
      cout<<std::to_string(sum);
      if(i) cout<<".";
      sum=0;
      base=1<<(8-1);
    }
  }
  cout<<endl;
  cout<<"num="<<sum<<" base="<<((long long int)1<<(bits-1))
      <<" size="<<size
      <<endl;
  std::cout<<num<<std::endl;
}

/*!
 * @brief   SFINAE std::string
 * @details std::string SFINAE print_ip function overload
 * @param[in] num integer variable that is expected to be converted to string
 * @tparam T std::string type
 * @return void
 */
template <class T>
typename std::enable_if<std::is_same<T,std::string>::value, void>::type
print_ip(T num)
{
  //cout<<"#2#"<<endl;
  std::cout<<num<<std::endl;
}

/*!
 * @brief   SFINAE std::list or std::vector
 * @details standard containers SFINAE print_ip function overload
 * @param[in] container integer variable that is expected to be converted to string
 * @tparam T standard C++ container type
 * @return void
 */
/*
template <class T>
typename std::enable_if<std::is_same<T,std::vector<int>>::value || std::is_same<T,std::list<int>>::value, void>::type
print_ip(T container)
{
  //cout<<"#3#"<<endl;
  int i=0;
  for(auto it=container.begin(); it != container.end(); ++it, ++i){
    cout<<*it;
    if(i != container.size()-1) cout<<".";
  }
  cout<<std::endl;
}
*/

template <class T>
typename std::enable_if<is_container<T>::value, void>::type
print_ip(T container)
{
  //cout<<"#3#"<<endl;
  int i=0;
  for(auto it=container.begin(); it != container.end(); ++it, ++i){
    cout<<*it;
    if(i != container.size()-1) cout<<".";
  }
  cout<<std::endl;
}

/*!
 * @brief   check if all std:tuple types are the same
 * @details check if all std:tuple types are the same
 * @param[in] tuple std::tuple
 * @tparam Head for compile-time recursion
 * @tparam Tail... the rest of the parameter pack
 */
template<typename Head, typename... Tail>
constexpr bool all_same(const std::tuple<Head, Tail...>&){
  return (std::is_same_v<Head,Tail> && ...);
}

constexpr bool all_same(const std::tuple<>&){return true;} 

template<size_t I=0, typename...Types>
void print_ip(const std::tuple<Types...> & tup){
  //cout<<"SIZE="<<(sizeof...(Types))<<endl;
  static_assert(all_same(tup));
  cout<<std::get<I>(tup);
  if constexpr(I+1 != sizeof...(Types) )
                cout<<".";
  if constexpr(I+1 != sizeof...(Types) )
                print_ip<I+1>(tup);
  if constexpr(I+1 == sizeof...(Types) )
                cout<<endl;
}

/*!
 * @brief Program entry point
 * @details Execution of the program starts here
 * @param[in] argc Number of arguments
 * @param[in] argv List of arguments
 * @return Program exit status
 */
int main(int argc, char** argv)
{
  print_ip(int8_t{-1});
  print_ip(int16_t{0});
  print_ip(int32_t{2130706433});
  print_ip(int64_t{8875824491850138409});
  print_ip(std::string("Hello, World!"));
  print_ip(std::vector<int>{100,200,300,400});
  print_ip(std::list<int>{400,300,200,100});
  print_ip(std::make_tuple(135,456,789,0)); 
  return 0;
}
