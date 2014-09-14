#include <iostream>
#include "random/random.h"
#include "staticshelper/cstatisticshelper.h"

int D4() { return ceng::Random( 1, 4 ); }
int D6() { return ceng::Random( 1, 6 ); }
int D8() { return ceng::Random( 1, 8 ); }
int D10() { return ceng::Random( 1, 10 ); }
int D12() { return ceng::Random( 1, 12 ); }
int D20() { return ceng::Random( 1, 20 ); }

int Reroll_D4() { int d4 = ceng::Random( 1, 4 ); while( d4 == 4 ) d4 = ceng::Random( 1, 4 ); return d4; }
int Reroll_D6() { int d6 = ceng::Random( 1, 6 ); while( d6 == 6 ) d6 = ceng::Random( 1, 6 ); return d6; }
int Reroll_D12() { int d12 = ceng::Random( 1, 12 ); while( d12 == 12 ) d12 = ceng::Random( 1, 12 ); return d12; }
int Reroll_D20() { int d20 = ceng::Random( 1, 20 ); while( d20 == 20 ) d20 = ceng::Random( 1, 20 ); return d20; }

/*
int D6() { return ceng::Random( 1, 6 ); }
int D8() { return ceng::Random( 1, 8 ); }
int D10() { return ceng::Random( 1, 10 ); }
int D12() { return ceng::Random( 1, 12 ); }
int D20() { return ceng::Random( 1, 20 ); }
*/

// --- no more money ---

int HowManyRoundsDoesItTake()
{
	int number_of_1s = 0;
	int req_crashes = 4;
	int number_of_rounds = 0;
	while( number_of_1s < req_crashes )
	{
		for( int i = 0; i < 1; ++i )
		{			
			if( Reroll_D4() <= 1 ) number_of_1s++;
			if( Reroll_D6() <= 1 ) number_of_1s++;
			if( Reroll_D12() <= 1 ) number_of_1s++;
			if( Reroll_D20() <= 1 ) number_of_1s++;
		}
		number_of_rounds++;
	}

	return number_of_rounds;
}

int DrawACard( std::vector< int >& deck_of_cards )
{
	if( deck_of_cards.empty() ) return 0;
	int r = ceng::Random( 0, (int)deck_of_cards.size() - 1 );
	int result = deck_of_cards[r];
	deck_of_cards[r] = deck_of_cards[ deck_of_cards.size() - 1 ];
	deck_of_cards.pop_back();
	return result;
}

int HowManyRoundsDoesItTake( std::vector< int > deck_of_cards, int& number_of_card_hits )
{
	int number_of_1s = 0;
	int req_crashes = 4;
	int number_of_rounds = 0;
	while( number_of_1s < req_crashes )
	{
		for( int i = 0; i < 1; ++i )
		{	
			int before = number_of_1s;
			if( D4() <= 1 ) number_of_1s++;
			if( D6() <= 1 ) number_of_1s++;
			if( D12() <= 1 ) number_of_1s++;
			if( D20() <= 1 ) number_of_1s++;

			if( number_of_1s == before && DrawACard( deck_of_cards ) == 1 ) {
				number_of_1s++;
				number_of_card_hits++;
			}
		}
		number_of_rounds++;
	}

	return number_of_rounds;
}


void PrintBarGraph( int r, int max_r )
{
	int n = (int)( ( (double)r / (double)max_r  ) * 300.0 + 0.5 );
	for( int i =0; i <n;++i )
	{
		std::cout << "-";
	}
}

void MonteCarloRounds()
{
	int monte_carlo_r = 1000000;
	double sum = 0;
	std::vector< int > mRoundCounts( 15 );
	ceng::math::CStatisticsHelper< int > mStats;

	std::vector< int > deck_of_cards;
	std::vector< int > mCardHits( 15 );
	for( int i = 0; i < 4; ++i ) deck_of_cards.push_back( 1 );
	for( int i = 0; i < 7; ++i ) deck_of_cards.push_back( 0 );


	for( int i = 0; i < monte_carlo_r; ++i )
	{
		int card_hits = 0;
		int r = HowManyRoundsDoesItTake( deck_of_cards, card_hits );
		mStats += r;
		if( r >= (int)mRoundCounts.size() )
			mRoundCounts.resize( r + 1 );
		mCardHits[r] += card_hits;

		mRoundCounts[r]++;

		sum += (double)r;
	}

	std::cout << "Average: " << sum / (double)monte_carlo_r << std::endl;
	std::cout << "Min: " << mStats.GetMin() << " , Max: " << mStats.GetMax() << std::endl;
	for( std::size_t i = 0; i < mRoundCounts.size(); ++i )
	{
		std::cout << ( i < 10 ? "0" : "" ) << i << " (";
		std::cout << ( mRoundCounts[i] > 0 ? ( (double)mCardHits[i] / (double)mRoundCounts[i] ) : 0 ) << "): "; 
		PrintBarGraph( mRoundCounts[i], monte_carlo_r );
		std::cout << std::endl;
	}

	for( std::size_t i = 0; i < mRoundCounts.size(); ++i )
	{
		std::cout << ( i < 10 ? "0" : "" ) << i << ": ";
		std::cout << mRoundCounts[i] << std::endl;
	}
}


int main( int argc, char** args )
{
	MonteCarloRounds();

	return 0;
}