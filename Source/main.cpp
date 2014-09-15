#include <iostream>
#include "random/random.h"
#include "staticshelper/cstatisticshelper.h"

int Test_D4()
{
	float f = ceng::Randomf( 0.f, 4.f );
	if( f <= 1.0f ) return 1;
	if( f <= 2.0f ) return 2;
	if( f <= 3.0f ) return 3;
	return 4;
}

int Test_D6()
{
	float f = ceng::Randomf( 0.f, 6.f );
	if( f <= 1.0f ) return 1;
	if( f <= 2.0f ) return 2;
	if( f <= 3.0f ) return 3;
	if( f <= 4.0f ) return 4;
	if( f <= 5.0f ) return 5;
	return 6;
}

int Test_D12()
{
	float f = ceng::Randomf( 0.f, 12.f );
	if( f <= 1.0f ) return 1;
	if( f <= 2.0f ) return 2;
	if( f <= 3.0f ) return 3;
	if( f <= 4.0f ) return 4;
	if( f <= 5.0f ) return 5;
	if( f <= 6.0f ) return 6;
	if( f <= 7.0f ) return 7;
	if( f <= 8.0f ) return 8;
	if( f <= 9.0f ) return 9;
	if( f <= 10.0f ) return 10;
	if( f <= 11.0f ) return 11;
	return 12;
}

int Test_D20()
{
	float f = ceng::Randomf( 0.f, 20.f );
	if( f <= 1.0f ) return 1;
	if( f <= 2.0f ) return 2;
	if( f <= 3.0f ) return 3;
	if( f <= 4.0f ) return 4;
	if( f <= 5.0f ) return 5;
	if( f <= 6.0f ) return 6;
	if( f <= 7.0f ) return 7;
	if( f <= 8.0f ) return 8;
	if( f <= 9.0f ) return 9;
	if( f <= 10.0f ) return 10;
	if( f <= 11.0f ) return 11;
	if( f <= 12.0f ) return 12;
	if( f <= 13.0f ) return 13;
	if( f <= 14.0f ) return 14;
	if( f <= 15.0f ) return 15;
	if( f <= 16.0f ) return 16;
	if( f <= 17.0f ) return 17;
	if( f <= 18.0f ) return 18;
	if( f <= 19.0f ) return 19;
	return 20;
}


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

int HowManyRoundsDoesItTake( int number_of_crashes = 5 )
{
	int number_of_1s = 0;
	int number_of_rounds = 0;
	while( number_of_1s < number_of_crashes )
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

int HowManyRoundsDoesItTake_NoRerolls( int number_of_crashes = 5 )
{
	int number_of_1s = 0;
	int number_of_rounds = 0;
	while( number_of_1s < number_of_crashes )
	{
		for( int i = 0; i < 1; ++i )
		{			
			if( D4() <= 1 ) number_of_1s++;
			if( D6() <= 1 ) number_of_1s++;
			if( D12() <= 1 ) number_of_1s++;
			if( D20() <= 1 ) number_of_1s++;
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

void PrintOutDieProbabilities()
{
	int monte_carlo_r = 1000000;

	// test if there are 4 1's in one round
	{
		// D4
		for( int j = 1; j <= 4; ++j )
		{
			int how_many_1s = 0;
			for( int i = 0; i < monte_carlo_r; ++i )
			{
				if( D4() == j ) 
					how_many_1s++;
			}
	
			std::cout << "D4(" << j << "): " <<  ((double)how_many_1s / (double)monte_carlo_r) * 100.0 << "%" << std::endl;
		}

		// D6
		for( int j = 1; j <= 6; ++j )
		{
			int how_many_1s = 0;
			for( int i = 0; i < monte_carlo_r; ++i )
			{
				if( D6() == j ) 
					how_many_1s++;
			}
	
			std::cout << "D6(" << j << "): " <<  ((double)how_many_1s / (double)monte_carlo_r) * 100.0 << "%" << std::endl;
		}

		// D12
		for( int j = 1; j <= 12; ++j )
		{
			int how_many_1s = 0;
			for( int i = 0; i < monte_carlo_r; ++i )
			{
				if( D12() == j ) 
					how_many_1s++;
			}
	
			std::cout << "D12(" << j << "): " <<  ((double)how_many_1s / (double)monte_carlo_r) * 100.0 << "%" << std::endl;
		}

		// D20
		for( int j = 1; j <= 20; ++j )
		{
			int how_many_1s = 0;
			for( int i = 0; i < monte_carlo_r; ++i )
			{
				if( D20() == j ) 
					how_many_1s++;
			}
	
			std::cout << "D20(" << j << "): " <<  ((double)how_many_1s / (double)monte_carlo_r) * 100.0 << "%" << std::endl;
		}
	}

	return;
}

void Prob_HowOftenOneAppears()
{
	int monte_carlo_r = 1000000;

	// D4
	int how_many_1s = 0;
	for( int i = 0; i < monte_carlo_r; ++i )
	{
		if( D4() <= 1 || D6() <= 1 || D12() <= 1 || D20() <= 1 )
			how_many_1s++;
	}

	std::cout << "Crash this round: " <<  ((double)how_many_1s / (double)monte_carlo_r) * 100.0 << "%" << std::endl;
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


void MonteCarloRounds_StandardGame()
{
	int monte_carlo_r = 1000000;

	double sum = 0;
	std::vector< int > mRoundCounts( 15 );
	ceng::math::CStatisticsHelper< int > mStats;

	for( int i = 0; i < monte_carlo_r; ++i )
	{
		int card_hits = 0;
		int r = HowManyRoundsDoesItTake( 4 );
		mStats += r;
		if( r >= (int)mRoundCounts.size() )
			mRoundCounts.resize( r + 1 );
		mRoundCounts[r]++;

		sum += (double)r;
	}

	std::cout << "Average: " << sum / (double)monte_carlo_r << std::endl;
	std::cout << "Min: " << mStats.GetMin() << " , Max: " << mStats.GetMax() << std::endl;
	for( std::size_t i = 0; i < mRoundCounts.size(); ++i )
	{
		std::cout << ( i < 10 ? "0" : "" ) << i << ": "; 
		PrintBarGraph( mRoundCounts[i], monte_carlo_r );
		std::cout << std::endl;
	}
}


int main( int argc, char** args )
{
	Prob_HowOftenOneAppears();
	MonteCarloRounds_StandardGame();
	// MonteCarloRounds();

	return 0;
}