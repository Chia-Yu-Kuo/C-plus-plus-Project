#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include <math.h>

using namespace std;

//��ƫŧi
int score (int[9]);





int main()
{//�ŧi
	char card[9] = { '2','S','R','O','Y','G','B','I','P' };//�d�P����
	//���õP
	char card_all[76] = { '2','2','2','2','2','2','2','2','2','2','S','S','S','R','O','Y','G','B','I','P','R','O','Y','G','B','I','P','R','O','Y','G','B','I','P','R','O','Y','G','B','I','P','R','O','Y','G','B','I','P','R','O','Y','G','B','I','P','R','O','Y','G','B','I','P','R','O','Y','G','B','I','P','R','O','Y','G','B','I','P' };
	srand(time(0));
	int i;
	cout << "�������A�X�Ѥd�A�d�P��:";
	for(i=1;i<=76;i++)
	{
		int j = rand() % (77 - i) + i;
		char t = card_all[i - 1];
		card_all[i - 1] = card_all[j - 1];
		card_all[j - 1] = t;		
		cout << card_all[i - 1];//test
	}
	cout << endl;
	
	int counter_all_card = 0;//�p������ѤU�����P

	bool game_end = 0;//�C�������P�_
	bool round_end = 0;//�^�X�����P�_

	bool player_have_take_card_end = 0;//���a�O�_���P�P�_
	bool AI1_have_take_card_end = 0;
	bool AI2_have_take_card_end = 0;
	bool AI3_have_take_card_end = 0;

	bool player_end = 0;//���a�����P�_
	bool AI1_end = 0;
	bool AI2_end = 0;
	bool AI3_end = 0;

	int counter_my[9] = {};
	int counter_AI1[9] = {};// '2','S','R','O','Y','G','B','I','P'������
	int counter_AI2[9] = {};
	int counter_AI3[9] = {};

	char card_my[4] = {};//�C�^�X�|���쪺�P�Ȯɦs
	char card_AI1[4] = {};                        
	char card_AI2[4] = {};
	char card_AI3[4] = {};
	
	char row1[4] = {'?','?','?'};//�Y'?','?','?':�o�C�٨S���P
	char row2[4] = {'?','?','?'};
	char row3[4] = {'?','?','?'};
	char row4[4] = {'?','?','?'};

	bool row1_end = 0;//row�٨S��:0
	bool row2_end = 0;
	bool row3_end = 0;
	bool row4_end = 0;

	char select ;//1:��P��P�B2:���O���P
	char draw_card;//�üƩ�쪺�P
	char put_card_row;//�n��b�ĴX�C?
	char take_card_row;//�n�����C?
	bool card_full_need_select2 = 0;//���F�n��row�������������a�o��select==1

	
	//explain the meaning of card
	cout << "The character of S means colorful" << endl;
	cout << "The character of 2 means +2" << endl;
	cout << "The character of R means red" << endl;
	cout << "The character of O means orange" << endl;
	cout << "The character of Y means yellow" << endl;
	cout << "The character of G means green" << endl;
	cout << "The character of B means blue" << endl;
	cout << "The character of I means lndigo" << endl;
	cout << "The character of P means purple" << endl;
					  
					  
					  
	//�o�P
	{
		int i = 0;
		int j = 0;
		int k = 0;
		int l = 0;

		do
		{
			card_my[0] = card_all[i];
			i++;
		} while (card_my[0] == 'S' || card_my[0] == '2');

		do
		{
			card_AI1[0] = card_all[j];
			j++;
		} while (card_AI1[0] == 'S' || card_AI1[0] == '2' || card_AI1[0] == card_my[0]);

		do
		{
			card_AI2[0] = card_all[k];
			k++;
		} while (card_AI2[0] == 'S' || card_AI2[0] == '2' || card_AI2[0] == card_my[0] || card_AI2[0] == card_AI1[0]);

		do
		{
			card_AI3[0] = card_all[l];
			l++;
		} while (card_AI3[0] == 'S' || card_AI3[0] == '2' || card_AI3[0] == card_my[0] || card_AI3[0] == card_AI1[0] || card_AI3[0] == card_AI2[0]);

		//counter++
		//my
		if (card_my[0] == '2')
		{
			counter_my[0]++;
		}
		else if (card_my[0] == 'S')
		{
			counter_my[1]++;
		}
		else if (card_my[0] == 'R')
		{
			counter_my[2]++;
		}
		else if (card_my[0] == 'O')
		{
			counter_my[3]++;
		}
		else if (card_my[0] == 'Y')
		{
			counter_my[4]++;
		}
		else if (card_my[0] == 'G')
		{
			counter_my[5]++;
		}
		else if (card_my[0] == 'B')
		{
			counter_my[6]++;
		}
		else if (card_my[0] == 'I')
		{
			counter_my[7]++;
		}
		else if (card_my[0] == 'P')
		{
			counter_my[8]++;
		}
		//AI1
		if (card_AI1[0] == '2')
		{
			counter_AI1[0]++;
		}
		else if (card_AI1[0] == 'S')
		{
			counter_AI1[1]++;
		}
		else if (card_AI1[0] == 'R')
		{
			counter_AI1[2]++;
		}
		else if (card_AI1[0] == 'O')
		{
			counter_AI1[3]++;
		}
		else if (card_AI1[0] == 'Y')
		{
			counter_AI1[4]++;
		}
		else if (card_AI1[0] == 'G')
		{
			counter_AI1[5]++;
		}
		else if (card_AI1[0] == 'B')
		{
			counter_AI1[6]++;
		}
		else if (card_AI1[0] == 'I')
		{
			counter_AI1[7]++;
		}
		else if (card_AI1[0] == 'P')
		{
			counter_AI1[8]++;
		}
	    //AI2
		if (card_AI2[0] == '2')
		{
			counter_AI2[0]++;
		}
		else if (card_AI2[0] == 'S')
		{
			counter_AI2[1]++;
		}
		else if (card_AI2[0] == 'R')
		{
			counter_AI2[2]++;
		}
		else if (card_AI2[0] == 'O')
		{
			counter_AI2[3]++;
		}
		else if (card_AI2[0] == 'Y')
		{
			counter_AI2[4]++;
		}
		else if (card_AI2[0] == 'G')
		{
			counter_AI2[5]++;
		}
		else if (card_AI2[0] == 'B')
		{
			counter_AI2[6]++;
		}
		else if (card_AI2[0] == 'I')
		{
			counter_AI2[7]++;
		}
		else if (card_AI2[0] == 'P')
		{
			counter_AI2[8]++;
		}
		//AI3
		if (card_AI3[0] == '2')
		{
			counter_AI3[0]++;
		}
		else if (card_AI3[0] == 'S')
		{
			counter_AI3[1]++;
		}
		else if (card_AI3[0] == 'R')
		{
			counter_AI3[2]++;
		}
		else if (card_AI3[0] == 'O')
		{
			counter_AI3[3]++;
		}
		else if (card_AI3[0] == 'Y')
		{
			counter_AI3[4]++;
		}
		else if (card_AI3[0] == 'G')
		{
			counter_AI3[5]++;
		}
		else if (card_AI3[0] == 'B')
		{
			counter_AI3[6]++;
		}
		else if (card_AI3[0] == 'I')
		{
			counter_AI3[7]++;
		}
		else if (card_AI3[0] == 'P')
		{
			counter_AI3[8]++;
		}
	
		card_all[i-1] = '@';
		card_all[j-1] = '@';
		card_all[k-1] = '@';
		card_all[l-1] = '@';

	}

	




	while (game_end==0)
	{
		round_end = 0;//��������bool�k�s

		row1_end = 0;
		row2_end = 0;
		row3_end = 0;
		row4_end = 0;

		player_have_take_card_end = 0;
		AI1_have_take_card_end = 0;
		AI2_have_take_card_end = 0;
		AI3_have_take_card_end = 0;

		card_full_need_select2 = 0;

		
		
		while (round_end==0)
		{
			if (player_have_take_card_end == 0)
			{
				player_end = 0;
				while (player_end==0)
				{
					//���
					cout << endl;
					cout << "player display" << endl;
					cout << "The card that players have amd row have currently" << endl;
					cout << "player:" << ' ' << card[0] << '*' << counter_my[0] << ' ' << card[1] << '*' << counter_my[1] << ' ' << card[2] << '*' << counter_my[2] << ' ' << card[3] << '*' << counter_my[3] << ' ' << card[4] << '*' << counter_my[4] << ' ' << card[5] << '*' << counter_my[5] << ' ' << card[6] << '*' << counter_my[6] << ' ' << card[7] << '*' << counter_my[7] << ' ' << card[8] << '*' << counter_my[8] << endl;
					cout << "AI1:" << ' ' << card[0] << '*' << counter_AI1[0] << ' ' << card[1] << '*' << counter_AI1[1] << ' ' << card[2] << '*' << counter_AI1[2] << ' ' << card[3] << '*' << counter_AI1[3] << ' ' << card[4] << '*' << counter_AI1[4] << ' ' << card[5] << '*' << counter_AI1[5] << ' ' << card[6] << '*' << counter_AI1[6] << ' ' << card[7] << '*' << counter_AI1[7] << ' ' << card[8] << '*' << counter_AI1[8] << endl;
					cout << "AI2:" << ' ' << card[0] << '*' << counter_AI2[0] << ' ' << card[1] << '*' << counter_AI2[1] << ' ' << card[2] << '*' << counter_AI2[2] << ' ' << card[3] << '*' << counter_AI2[3] << ' ' << card[4] << '*' << counter_AI2[4] << ' ' << card[5] << '*' << counter_AI2[5] << ' ' << card[6] << '*' << counter_AI2[6] << ' ' << card[7] << '*' << counter_AI2[7] << ' ' << card[8] << '*' << counter_AI2[8] << endl;
					cout << "AI3:" << ' ' << card[0] << '*' << counter_AI3[0] << ' ' << card[1] << '*' << counter_AI3[1] << ' ' << card[2] << '*' << counter_AI3[2] << ' ' << card[3] << '*' << counter_AI3[3] << ' ' << card[4] << '*' << counter_AI3[4] << ' ' << card[5] << '*' << counter_AI3[5] << ' ' << card[6] << '*' << counter_AI3[6] << ' ' << card[7] << '*' << counter_AI3[7] << ' ' << card[8] << '*' << counter_AI3[8] << endl;
					cout << endl;

					if (row1_end==0)
					{					
						cout << "Row1: ";
						for (size_t i = 0; i < 3; i++)
						{
							cout << row1[i]<<' ';
						}
						cout << endl;
					}
					if (row2_end==0)
					{					
						cout << "Row2: ";
						for (size_t i = 0; i < 3; i++)
						{
							cout  << row2[i] << ' ';
						}
						cout << endl;
					}
					if (row3_end==0)
					{					
						cout << "Row3: ";
						for (size_t i = 0; i < 3; i++)
						{
							cout << row3[i] << ' ';
						}
						cout << endl;
					}
					if (row4_end==0)
					{					
						cout << "Row4: ";
						for (size_t i = 0; i < 3; i++)
						{
							cout << row4[i] << ' ';
						}
						cout << endl;
					}






					cout << "�n��Ʃ�P��J1   �A�n���O���P��J2  " << endl;
					cin >> select;

					/*			//���b

					bool judge;

					do//���b
					{
						bool judge;
						double k,mod,n=0;


						judge = 0;
						k = strlen(select);
						for (size_t i = 0; i < k; i++)
						{
							if (select[i] > 57 || select[i] < 48)
							{
								judge = 1;
							}
						}



						double f = atof(select);
						mod = fmod(f, 1);
						if (f > 0 && judge == 0 && mod == 0)
						{
							judge = 2;
							n = f;
							break;
						}

						else
						{
							judge = 1;
						}
						if (judge == 1)
						{
							cout << "input error" << endl;
							cout << "Please input a positive integer :" << endl;
							cin >> select;
						}

					} while (judge == 1);
*/

					while (select!='1' && select!='2')
					{
						cout << "input error" << endl;
						cout << "�n��Ʃ�P��J1   �A�n���O���P��J2" << endl;
						cin >> select;
					}

					if (card_full_need_select2==1&&select==1)
					{
						cout << "�����P�F�A�u�ள�P" << endl;
						select = 2;
					}

					if (select=='1')//���P
					{
						int u = 0;
						do//��
						{
							draw_card = card_all[u];
							u++;
						} while (draw_card == '@');
						card_all[u - 1] = '@';
						cout << draw_card << endl;//test

						while (true)
						{
							cout << "�n��b�ĴX�C?(1�B2�B3�B4)"<<endl;
							cin >> put_card_row;
							//row1�P�_
							if (put_card_row == '1')
							{
								if (row1_end == 0)
								{
									if ( row1[0] == '?' || row1[1] == '?' || row1[2] == '?')
									{
										if (row1[0] == '?')
										{
											row1[0] = draw_card;
											break;
										}
										else if(row1[1] == '?')
										{
											row1[1] = draw_card;
											break;
										}
										else if (row1[2] == '?')
										{
											row1[2] = draw_card;
											break;
										}
									}
									else
									{
										cout << "�o�C�w���A�Ч��L�C" << endl;
										continue;
									}
								}
								else
								{
								cout << "���^�X���C�w�Q�飼�A�Ч��L�C" << endl;
								continue;
								}
							}
						
							//row2
							else if (put_card_row == '2')
							{
									if (row2_end == 0)
									{
										if (row2[0] == '?' || row2[1] == '?' || row2[2] == '?')
										{
											if (row2[0] == '?')
											{
												row2[0] = draw_card;
												break;
											}
											else if (row2[1] == '?')
											{
												row2[1] = draw_card;
												break;
											}
											else if (row2[2] == '?')
											{
												row2[2] = draw_card;
												break;
											}
										}
										else
										{
											cout << "�o�C�w���A�Ч��L�C" << endl;
											continue;
										}
									}
									else
									{
										cout << "���^�X���C�w�Q�飼�A�Ч��L�C" << endl;
										continue;
									}
							}
						

							//row3
							else if (put_card_row == '3')
							{
									if (row3_end == 0)
									{
										if (row3[0] == '?' || row3[1] == '?' || row3[2] == '?')
										{
											if (row3[0] == '?')
											{
												row3[0] = draw_card;
												break;
											}
											else if (row3[1] == '?')
											{
												row3[1] = draw_card;
												break;
											}
											else if (row3[2] == '?')
											{
												row3[2] = draw_card;
												break;
											}
										}
										else
										{
											cout << "�o�C�w���A�Ч��L�C" << endl;
											continue;
										}
									}
									else
									{
										cout << "���^�X���C�w�Q�飼�A�Ч��L�C" << endl;
										continue;
									}
							}
						
						
							//row4
							else if (put_card_row == '4')
							{
									if (row4_end == 0)
									{
										if (row4[0] == '?' || row4[1] == '?' || row4[2] == '?')
										{
											if (row4[0] == '?')
											{
												row4[0] = draw_card;
												break;
											}
											else if (row4[1] == '?')
											{
												row4[1] = draw_card;
												break;
											}
											else if (row4[2] == '?')
											{
												row4[2] = draw_card;
												break;
											}
										}
										else
										{
											cout << "�o�C�w���A�Ч��L�C" << endl;
											continue;
										}
									}
									else
									{
										cout << "���^�X���C�w�Q�飼�A�Ч��L�C" << endl;
										continue;
									}
							}
							else
							{
							cout << "input error" << endl;
							continue;
							}
						
						}
						player_end = 1;
						
					}



					if (select == '2')//���O���P
					{
						if (row1[0]== '?'&& row2[0] == '?' && row3[0] == '?' && row4[0] == '?')
						{
							cout << "�S���P���A��"<<endl;
							continue;
						}
						else
						{
							while (true)
							{
								cout << "�n����@�C�O?" << endl;
								cin >> take_card_row;//���b
							
							

								switch (take_card_row)
								{
								case '1':
									if (row1[0]!= '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row1[i]!= '?')
											{
												card_my[i] = row1[i];
												row1[i] = {'?'};
												row1_end = 1;
											}
										}
										row1_end = 1;
									}
									else
									{
										cout<<"�o��w�Q�飼�F�A�άO���W�S�P" << endl;
										continue;
									}
									break;
								case '2' :
									if (row2[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row2[i] != '?')
											{
												card_my[i] = row2[i];
												row2[i] = { '?' };
												row2_end = 1;
											}
										}
										row2_end = 1;
									}
									else
									{
										cout << "�o��w�Q�飼�F�A�άO���W�S�P" << endl;
										continue;
									}
									break;
								case '3':
									if (row3[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row3[i] != '?')
											{
												card_my[i] = row3[i];
												row3[i] = { '?' };
												row3_end = 1;
											}
										}
										row3_end = 1;
									}
									else
									{
										cout << "�o��w�Q�飼�F�A�άO���W�S�P" << endl;
										continue;
									}
									break;
								case '4':
									if (row4[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row4[i] != '?')
											{
												card_my[i] = row4[i];
												row4[i] = { '?' };
												row4_end = 1;
											}
										}
										row4_end = 1;
									}
									else
									{
										cout << "�o��w�Q�飼�F�A�άO���W�S�P" << endl;
										continue;
									}
									break;
								default:
									cout << "input error" << endl;

									continue;
								}

								if (card_my[0]!='\0')
								{
									break;          //�Ҽ{�n�B�n�[
								}
						
							} 

							//counter++
							for (size_t i = 0; i < 3; i++)
							{
								if (card_my[i]=='2')
								{
									counter_my[0]++;
								}
								else if (card_my[i] == 'S')
								{
									counter_my[1]++;
								}
								else if (card_my[i] == 'R')
								{
									counter_my[2]++;
								}
								else if (card_my[i] == 'O')
								{
									counter_my[3]++;
								}
								else if (card_my[i] == 'Y')
								{
									counter_my[4]++;
								}
								else if (card_my[i] == 'G')
								{
									counter_my[5]++;
								}
								else if (card_my[i] == 'B')
								{
									counter_my[6]++;
								}
								else if (card_my[i] == 'I')
								{
									counter_my[7]++;
								}
								else if (card_my[i] == 'P')
								{
									counter_my[8]++;
								}
								else
								{
									break;
								}							
							}
							for (size_t i = 0; i < 3; i++)
							{
								card_my[i] = { '0' };
							}						

							player_end = 1;//my ����
							player_have_take_card_end = 1;//�w���P
						}
					}
					//��Select==1
					if ((row1_end == 1 && row2_end == 1 && row3_end == 1 && row4[2] != '?') || (row1_end == 1 && row2_end == 1 && row4_end == 1 && row3[2] != '?') || (row1_end == 1 && row4_end == 1 && row3_end == 1 && row2[2] != '?') || (row4_end == 1 && row2_end == 1 && row3_end == 1 && row1[2] != '?')||(row1_end == 1 && row2_end == 1 && row3[2] != '?' && row4[2] != '?')||(row1_end == 1 && row3_end == 1 && row2[2] != '?' && row4[2] != '?')||(row1_end == 1 && row4_end == 1 && row3[2] != '?' && row2[2] != '?')||(row3_end == 1 && row2_end == 1 && row1[2] != '?' && row4[2] != '?')||(row4_end == 1 && row2_end == 1 && row3[2] != '?' && row1[2] != '?') || (row3_end == 1 && row4_end == 1 && row1[2] != '?' && row2[2] != '?'))
					{
						card_full_need_select2 = 1;
					}
				}
			}
			
			
			//AI1  test
			if (AI1_have_take_card_end==0)
			{
				//���
				
				cout << endl;
				cout <<"AI1 display"<< endl;
				cout << "The card that players have amd row have currently" << endl;
				cout << "player:" << ' ' << card[0] << '*' << counter_my[0] << ' ' << card[1] << '*' << counter_my[1] << ' ' << card[2] << '*' << counter_my[2] << ' ' << card[3] << '*' << counter_my[3] << ' ' << card[4] << '*' << counter_my[4] << ' ' << card[5] << '*' << counter_my[5] << ' ' << card[6] << '*' << counter_my[6] << ' ' << card[7] << '*' << counter_my[7] << ' ' << card[8] << '*' << counter_my[8] << endl;
				cout << "AI1:" << ' ' << card[0] << '*' << counter_AI1[0] << ' ' << card[1] << '*' << counter_AI1[1] << ' ' << card[2] << '*' << counter_AI1[2] << ' ' << card[3] << '*' << counter_AI1[3] << ' ' << card[4] << '*' << counter_AI1[4] << ' ' << card[5] << '*' << counter_AI1[5] << ' ' << card[6] << '*' << counter_AI1[6] << ' ' << card[7] << '*' << counter_AI1[7] << ' ' << card[8] << '*' << counter_AI1[8] << endl;
				cout << "AI2:" << ' ' << card[0] << '*' << counter_AI2[0] << ' ' << card[1] << '*' << counter_AI2[1] << ' ' << card[2] << '*' << counter_AI2[2] << ' ' << card[3] << '*' << counter_AI2[3] << ' ' << card[4] << '*' << counter_AI2[4] << ' ' << card[5] << '*' << counter_AI2[5] << ' ' << card[6] << '*' << counter_AI2[6] << ' ' << card[7] << '*' << counter_AI2[7] << ' ' << card[8] << '*' << counter_AI2[8] << endl;
				cout << "AI3:" << ' ' << card[0] << '*' << counter_AI3[0] << ' ' << card[1] << '*' << counter_AI3[1] << ' ' << card[2] << '*' << counter_AI3[2] << ' ' << card[3] << '*' << counter_AI3[3] << ' ' << card[4] << '*' << counter_AI3[4] << ' ' << card[5] << '*' << counter_AI3[5] << ' ' << card[6] << '*' << counter_AI3[6] << ' ' << card[7] << '*' << counter_AI3[7] << ' ' << card[8] << '*' << counter_AI3[8] << endl;
				cout << endl;

				if (row1_end == 0)
				{
					cout << "Row1: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row1[i] << ' ';
					}
					cout << endl;
				}
				if (row2_end == 0)
				{
					cout << "Row2: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row2[i] << ' ';
					}
					cout << endl;
				}
				if (row3_end == 0)
				{
					cout << "Row3: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row3[i] << ' ';
					}
					cout << endl;
				}
				if (row4_end == 0)
				{
					cout << "Row4: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row4[i] << ' ';
					}
					cout << endl;
				}


			
				AI1_end = 0;
				while (AI1_end==0)
				{
					select = (rand() % 2 + 1);

					if (card_full_need_select2 == 1 && select == 1)
					{
						select = 2;
					}



					//���
					if (select==1)
					{
						int u = 0;
						do//��
						{
							draw_card = card_all[u];
							u++;
						} while (draw_card == '@');
						card_all[u - 1] = '@';
				

			

						while (true)//��
						{
							put_card_row = (rand() % 4 + 1);//��C

					

							//row1
							if (put_card_row == 1)
							{
								if (row1_end == 0)
								{
									if (row1[0] == '?' || row1[1] == '?' || row1[2] == '?')
									{
										if (row1[0] == '?')
										{
											row1[0] = draw_card;
											break;
										}
										else if (row1[1] == '?')
										{
											row1[1] = draw_card;
											break;
										}
										else if (row1[2] == '?')
										{
											row1[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							
							}
					

							//row2
							if (put_card_row == 2)
							{
								if (row2_end == 0)
								{
									if (row2[0] == '?' || row2[1] == '?' || row2[2] == '?')
									{
										if (row2[0] == '?')
										{
											row2[0] = draw_card;
											break;
										}
										else if (row2[1] == '?')
										{
											row2[1] = draw_card;
											break;
										}
										else if (row2[2] == '?')
										{
											row2[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
				

							//row3
							if (put_card_row == 3)
							{
								if (row3_end == 0)
								{
									if (row3[0] == '?' || row3[1] == '?' || row3[2] == '?')
									{
										if (row3[0] == '?')
										{
											row3[0] = draw_card;
											break;
										}
										else if (row3[1] == '?')
										{
											row3[1] = draw_card;
											break;
										}
										else if (row3[2] == '?')
										{
											row3[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
				

							//row4
							if (put_card_row == 4)
							{
								if (row4_end == 0)
								{
									if (row4[0] == '?' || row4[1] == '?' || row4[2] == '?')
									{
										if (row4[0] == '?')
										{
											row4[0] = draw_card;
											break;
										}
										else if (row4[1] == '?')
										{
											row4[1] = draw_card;
											break;
										}
										else if (row4[2] == '?')
										{
											row4[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
						}
						AI1_end = 1;
						
					} 


				

					//���O���P
					if (select==2)
					{
						if (row1[0] == '?'&& row2[0] == '?' && row3[0] == '?' && row4[0] == '?')
						{
							continue;
						}
						else
						{
							while (true)
							{
								take_card_row = (rand() % 4 + 1);

								switch (take_card_row)
								{
									case 1:
										if (row1[0] != '?')
										{
											for (size_t i = 0; i < 3; i++)
											{
												if (row1[i] != '?')
												{
													card_AI1[i] = row1[i];
													row1[i] = { '?' };
													row1_end = 1;
												}
											}
											row1_end = 1;
										}
										else
										{
											continue;
										}
										break;
									case 2:
										if (row2[0] != '?')
										{
											for (size_t i = 0; i < 3; i++)
											{
												if (row2[i] != '?')
												{
													card_AI1[i] = row2[i];
													row2[i] = { '?' };
													row2_end = 1;
												}
											}
											row2_end = 1;
										}
										else
										{
											continue;
										}
										break;
									case 3:
										if (row3[0] != '?')
										{
											for (size_t i = 0; i < 3; i++)
											{
												if (row3[i] != '?')
												{
													card_AI1[i] = row3[i];
													row3[i] = { '?' };
													row3_end = 1;
												}
											}
											row3_end = 1;
										}
										else
										{								
											continue;
										}
										break;
									case 4:
										if (row4[0] != '?')
										{
											for (size_t i = 0; i < 3; i++)
											{
												if (row4[i] != '?')
												{
													card_AI1[i] = row4[i];
													row4[i] = { '?' };
													row4_end = 1;
												}
											}
											row4_end = 1;
										}
										else
										{								
											continue;
										}
										break;

									default:							
										continue;
								}



								break;
							} 

						

							//counter++
							for (size_t i = 0; i < 3; i++)
							{
								if (card_AI1[i] == '2')
								{
									counter_AI1[0]++;
								}
								else if (card_AI1[i] == 'S')
								{
									counter_AI1[1]++;
								}
								else if (card_AI1[i] == 'R')
								{
									counter_AI1[2]++;
								}
								else if (card_AI1[i] == 'O')
								{
									counter_AI1[3]++;
								}
								else if (card_AI1[i] == 'Y')
								{
									counter_AI1[4]++;
								}
								else if (card_AI1[i] == 'G')
								{
									counter_AI1[5]++;
								}
								else if (card_AI1[i] == 'B')
								{
									counter_AI1[6]++;
								}
								else if (card_AI1[i] == 'I')
								{
									counter_AI1[7]++;
								}
								else if (card_AI1[i] == 'P')
								{
									counter_AI1[8]++;
								}
								else
								{
									break;
								}
							
							}
							for (size_t i = 0; i < 3; i++)
							{
								card_AI1[i] = { '0' };
							}
							AI1_end = 1;//AI1 ����
							AI1_have_take_card_end = 1;
						}
					}
					if ((row1_end == 1 && row2_end == 1 && row3_end == 1 && row4[2] != '?') || (row1_end == 1 && row2_end == 1 && row4_end == 1 && row3[2] != '?') || (row1_end == 1 && row4_end == 1 && row3_end == 1 && row2[2] != '?') || (row4_end == 1 && row2_end == 1 && row3_end == 1 && row1[2] != '?') || (row1_end == 1 && row2_end == 1 && row3[2] != '?' && row4[2] != '?') || (row1_end == 1 && row3_end == 1 && row2[2] != '?' && row4[2] != '?') || (row1_end == 1 && row4_end == 1 && row3[2] != '?' && row2[2] != '?') || (row3_end == 1 && row2_end == 1 && row1[2] != '?' && row4[2] != '?') || (row4_end == 1 && row2_end == 1 && row3[2] != '?' && row1[2] != '?') || (row3_end == 1 && row4_end == 1 && row1[2] != '?' && row2[2] != '?'))
					{
						card_full_need_select2 = 1;
					}
				}
			
			}
			
			
			
			//AI2


			if (AI2_have_take_card_end==0)
			{
				//���   test
				cout << endl;
				cout << "AI2 display" << endl;
				cout << "The card that players have amd row have currently" << endl;
				cout << "player:" << ' ' << card[0] << '*' << counter_my[0] << ' ' << card[1] << '*' << counter_my[1] << ' ' << card[2] << '*' << counter_my[2] << ' ' << card[3] << '*' << counter_my[3] << ' ' << card[4] << '*' << counter_my[4] << ' ' << card[5] << '*' << counter_my[5] << ' ' << card[6] << '*' << counter_my[6] << ' ' << card[7] << '*' << counter_my[7] << ' ' << card[8] << '*' << counter_my[8] << endl;
				cout << "AI1:" << ' ' << card[0] << '*' << counter_AI1[0] << ' ' << card[1] << '*' << counter_AI1[1] << ' ' << card[2] << '*' << counter_AI1[2] << ' ' << card[3] << '*' << counter_AI1[3] << ' ' << card[4] << '*' << counter_AI1[4] << ' ' << card[5] << '*' << counter_AI1[5] << ' ' << card[6] << '*' << counter_AI1[6] << ' ' << card[7] << '*' << counter_AI1[7] << ' ' << card[8] << '*' << counter_AI1[8] << endl;
				cout << "AI2:" << ' ' << card[0] << '*' << counter_AI2[0] << ' ' << card[1] << '*' << counter_AI2[1] << ' ' << card[2] << '*' << counter_AI2[2] << ' ' << card[3] << '*' << counter_AI2[3] << ' ' << card[4] << '*' << counter_AI2[4] << ' ' << card[5] << '*' << counter_AI2[5] << ' ' << card[6] << '*' << counter_AI2[6] << ' ' << card[7] << '*' << counter_AI2[7] << ' ' << card[8] << '*' << counter_AI2[8] << endl;
				cout << "AI3:" << ' ' << card[0] << '*' << counter_AI3[0] << ' ' << card[1] << '*' << counter_AI3[1] << ' ' << card[2] << '*' << counter_AI3[2] << ' ' << card[3] << '*' << counter_AI3[3] << ' ' << card[4] << '*' << counter_AI3[4] << ' ' << card[5] << '*' << counter_AI3[5] << ' ' << card[6] << '*' << counter_AI3[6] << ' ' << card[7] << '*' << counter_AI3[7] << ' ' << card[8] << '*' << counter_AI3[8] << endl;
				cout << endl;

				if (row1_end == 0)
				{
					cout << "Row1: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row1[i] << ' ';
					}
					cout << endl;
				}
				if (row2_end == 0)
				{
					cout << "Row2: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row2[i] << ' ';
					}
					cout << endl;
				}
				if (row3_end == 0)
				{
					cout << "Row3: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row3[i] << ' ';
					}
					cout << endl;
				}
				if (row4_end == 0)
				{
					cout << "Row4: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row4[i] << ' ';
					}
					cout << endl;
				}


			
				AI2_end = 0;
				while (AI2_end == 0)
				{
					select = (rand() % 2 + 1);

					if (card_full_need_select2 == 1 && select == 1)
					{
						select = 2;
					}

					//���
					if (select == 1)
					{
						int u = 0;
						do//��
						{
							draw_card = card_all[u];
							u++;
						} while (draw_card == '@');
						card_all[u - 1] = '@';
				


						while (true)//��
						{
							put_card_row = (rand() % 4 + 1);//��C

							//row1
							if (put_card_row == 1)
							{
								if (row1_end == 0)
								{
									if (row1[0] == '?' || row1[1] == '?' || row1[2] == '?')
									{
										if (row1[0] == '?')
										{
											row1[0] = draw_card;
											break;
										}
										else if (row1[1] == '?')
										{
											row1[1] = draw_card;
											break;
										}
										else if (row1[2] == '?')
										{
											row1[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
						

							//row2
							if (put_card_row == 2)
							{
								if (row2_end == 0)
								{
									if (row2[0] == '?' || row2[1] == '?' || row2[2] == '?')
									{
										if (row2[0] == '?')
										{
											row2[0] = draw_card;
											break;
										}
										else if (row2[1] == '?')
										{
											row2[1] = draw_card;
											break;
										}
										else if (row2[2] == '?')
										{
											row2[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
					

							//row3
							if (put_card_row == 3)
							{
								if (row3_end == 0)
								{
									if (row3[0] == '?' || row3[1] == '?' || row3[2] == '?')
									{
										if (row3[0] == '?')
										{
											row3[0] = draw_card;
											break;
										}
										else if (row3[1] == '?')
										{
											row3[1] = draw_card;
											break;
										}
										else if (row3[2] == '?')
										{
											row3[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
						

							//row4
							if (put_card_row == 4)
							{
								if (row4_end == 0)
								{
									if (row4[0] == '?' || row4[1] == '?' || row4[2] == '?')
									{
										if (row4[0] == '?')
										{
											row4[0] = draw_card;
											break;
										}
										else if (row4[1] == '?')
										{
											row4[1] = draw_card;
											break;
										}
										else if (row4[2] == '?')
										{
											row4[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
						
						}
						AI2_end = 1;
						
					}



					//���O���P
					if (select == 2)
					{
						if (row1[0] == '?'&& row2[0] == '?' && row3[0] == '?' && row4[0] == '?')
						{
							continue;
						}
						else
						{
							while (true)
							{
								take_card_row = (rand() % 4 + 1);

								switch (take_card_row)
								{
								case 1:
									if (row1[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row1[i] != '?')
											{
												card_AI2[i] = row1[i];
												row1[i] = { '?' };
												row1_end = 1;
											}
										}
										row1_end = 1;
									}
									else
									{
										continue;
									}
									break;
								case 2:
									if (row2[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row2[i] != '?')
											{
												card_AI2[i] = row2[i];
												row2[i] = { '?' };
												row2_end = 1;
											}
										}
										row2_end = 1;
									}
									else
									{
										continue;
									}
									break;
								case 3:
									if (row3[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row3[i] != '?')
											{
												card_AI2[i] = row3[i];
												row3[i] = { '?' };
												row3_end = 1;
											}
										}
										row3_end = 1;
									}
									else
									{
										continue;
									}
									break;
								case 4:
									if (row4[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row4[i] != '?')
											{
												card_AI2[i] = row4[i];
												row4[i] = { '?' };
												row4_end = 1;
											}
										}
										row3_end = 1;
									}
									else
									{
										continue;
									}
									break;
								default:
									continue;
								}



								break;
							} 

							//counter++
							for (size_t i = 0; i < 3; i++)
							{
								if (card_AI2[i] == '2')
								{
									counter_AI2[0]++;
								}
								else if (card_AI2[i] == 'S')
								{
									counter_AI2[1]++;
								}
								else if (card_AI2[i] == 'R')
								{
									counter_AI2[2]++;
								}
								else if (card_AI2[i] == 'O')
								{
									counter_AI2[3]++;
								}
								else if (card_AI2[i] == 'Y')
								{
									counter_AI2[4]++;
								}
								else if (card_AI2[i] == 'G')
								{
									counter_AI2[5]++;
								}
								else if (card_AI2[i] == 'B')
								{
									counter_AI2[6]++;
								}
								else if (card_AI2[i] == 'I')
								{
									counter_AI2[7]++;
								}
								else if (card_AI2[i] == 'P')
								{
									counter_AI2[8]++;
								}
								else
								{
									break;
								}

							}
							for (size_t i = 0; i < 3; i++)
							{
								card_AI2[i] = { '0' };
							}

							AI2_end = 1;//AI2 ����
							AI2_have_take_card_end = 1;
						}
					}
					if ((row1_end == 1 && row2_end == 1 && row3_end == 1 && row4[2] != '?') || (row1_end == 1 && row2_end == 1 && row4_end == 1 && row3[2] != '?') || (row1_end == 1 && row4_end == 1 && row3_end == 1 && row2[2] != '?') || (row4_end == 1 && row2_end == 1 && row3_end == 1 && row1[2] != '?') || (row1_end == 1 && row2_end == 1 && row3[2] != '?' && row4[2] != '?') || (row1_end == 1 && row3_end == 1 && row2[2] != '?' && row4[2] != '?') || (row1_end == 1 && row4_end == 1 && row3[2] != '?' && row2[2] != '?') || (row3_end == 1 && row2_end == 1 && row1[2] != '?' && row4[2] != '?') || (row4_end == 1 && row2_end == 1 && row3[2] != '?' && row1[2] != '?') || (row3_end == 1 && row4_end == 1 && row1[2] != '?' && row2[2] != '?'))
					{
						card_full_need_select2 = 1;
					}
				}

			}

			//AI3
			if (AI3_have_take_card_end==0)
			{
				//���  test
				cout << endl;
				cout << "AI3 display" << endl;
				cout << "The card that players have amd row have currently" << endl;
				cout << "player:" << ' ' << card[0] << '*' << counter_my[0] << ' ' << card[1] << '*' << counter_my[1] << ' ' << card[2] << '*' << counter_my[2] << ' ' << card[3] << '*' << counter_my[3] << ' ' << card[4] << '*' << counter_my[4] << ' ' << card[5] << '*' << counter_my[5] << ' ' << card[6] << '*' << counter_my[6] << ' ' << card[7] << '*' << counter_my[7] << ' ' << card[8] << '*' << counter_my[8] << endl;
				cout << "AI1:" << ' ' << card[0] << '*' << counter_AI1[0] << ' ' << card[1] << '*' << counter_AI1[1] << ' ' << card[2] << '*' << counter_AI1[2] << ' ' << card[3] << '*' << counter_AI1[3] << ' ' << card[4] << '*' << counter_AI1[4] << ' ' << card[5] << '*' << counter_AI1[5] << ' ' << card[6] << '*' << counter_AI1[6] << ' ' << card[7] << '*' << counter_AI1[7] << ' ' << card[8] << '*' << counter_AI1[8] << endl;
				cout << "AI2:" << ' ' << card[0] << '*' << counter_AI2[0] << ' ' << card[1] << '*' << counter_AI2[1] << ' ' << card[2] << '*' << counter_AI2[2] << ' ' << card[3] << '*' << counter_AI2[3] << ' ' << card[4] << '*' << counter_AI2[4] << ' ' << card[5] << '*' << counter_AI2[5] << ' ' << card[6] << '*' << counter_AI2[6] << ' ' << card[7] << '*' << counter_AI2[7] << ' ' << card[8] << '*' << counter_AI2[8] << endl;
				cout << "AI3:" << ' ' << card[0] << '*' << counter_AI3[0] << ' ' << card[1] << '*' << counter_AI3[1] << ' ' << card[2] << '*' << counter_AI3[2] << ' ' << card[3] << '*' << counter_AI3[3] << ' ' << card[4] << '*' << counter_AI3[4] << ' ' << card[5] << '*' << counter_AI3[5] << ' ' << card[6] << '*' << counter_AI3[6] << ' ' << card[7] << '*' << counter_AI3[7] << ' ' << card[8] << '*' << counter_AI3[8] << endl;
				cout << endl;

				if (row1_end == 0)
				{
					cout << "Row1: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row1[i] << ' ';
					}
					cout << endl;
				}
				if (row2_end == 0)
				{
					cout << "Row2: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row2[i] << ' ';
					}
					cout << endl;
				}
				if (row3_end == 0)
				{
					cout << "Row3: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row3[i] << ' ';
					}
					cout << endl;
				}
				if (row4_end == 0)
				{
					cout << "Row4: ";
					for (size_t i = 0; i < 3; i++)
					{
						cout << row4[i] << ' ';
					}
					cout << endl;
				}


			
				AI3_end = 0;
				while (AI3_end == 0)
				{
					srand((unsigned)time(0));
					select = (rand() % 2 + 1);

					if (card_full_need_select2 == 1 && select == 1)
					{
						select = 2;
					}

					//���
					if (select == 1)
					{
						int u = 0;
						do//��
						{
							draw_card = card_all[u];
							u++;
						} while (draw_card == '@');
						card_all[u - 1] = '@';					
				


						while (true)//��
						{
							put_card_row = (rand() % 4 + 1);//��C

							//row1
							if (put_card_row == 1)
							{
								if (row1_end == 0)
								{
									if (row1[0] == '?' || row1[1] == '?' || row1[2] == '?')
									{
										if (row1[0] == '?')
										{
											row1[0] = draw_card;
											break;
										}
										else if (row1[1] == '?')
										{
											row1[1] = draw_card;
											break;
										}
										else if (row1[2] == '?')
										{
											row1[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
						

							//row2
							if (put_card_row == 2)
							{
								if (row2_end == 0)
								{
									if (row2[0] == '?' || row2[1] == '?' || row2[2] == '?')
									{
										if (row2[0] == '?')
										{
											row2[0] = draw_card;
											break;
										}
										else if (row2[1] == '?')
										{
											row2[1] = draw_card;
											break;
										}
										else if (row2[2] == '?')
										{
											row2[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
						

							//row3
							if (put_card_row == 3)
							{
								if (row3_end == 0)
								{
									if (row3[0] == '?' || row3[1] == '?' || row3[2] == '?')
									{
										if (row3[0] == '?')
										{
											row3[0] = draw_card;
											break;
										}
										else if (row3[1] == '?')
										{
											row3[1] = draw_card;
											break;
										}
										else if (row3[2] == '?')
										{
											row3[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
						

							//row4
							if (put_card_row == 4)
							{
								if (row4_end == 0)
								{
									if (row4[0] == '?' || row4[1] == '?' || row4[2] == '?')
									{
										if (row4[0] == '?')
										{
											row4[0] = draw_card;
											break;
										}
										else if (row4[1] == '?')
										{
											row4[1] = draw_card;
											break;
										}
										else if (row4[2] == '?')
										{
											row4[2] = draw_card;
											break;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
						
						}
						AI3_end = 1;
						
					}



					//���O���P
					if (select == 2)
					{
						if (row1[0] == '?'&& row2[0] == '?' && row3[0] == '?' && row4[0] == '?')
						{
							continue;
						}
						else
						{
							while (true)
							{
								take_card_row = (rand() % 4 + 1);

								switch (take_card_row)
								{
								case 1:
									if (row1[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row1[i] != '?')
											{
												card_AI3[i] = row1[i];
												row1[i] = { '?' };
												row1_end = 1;
											}
										}
										row1_end = 1;
									}
									else
									{
										continue;
									}
									break;
								case 2:
									if (row2[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row2[i] != '?')
											{
												card_AI3[i] = row2[i];
												row2[i] = { '?' };
												row2_end = 1;
											}
										}
										row2_end = 1;
									}
									else
									{
										continue;
									}
									break;
								case 3:
									if (row3[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row3[i] != '?')
											{
												card_AI3[i] = row3[i];
												row3[i] = { '?' };
												row3_end = 1;
											}
										}
										row3_end = 1;
									}
									else
									{
										continue;
									}
									break;
								case 4:
									if (row4[0] != '?')
									{
										for (size_t i = 0; i < 3; i++)
										{
											if (row4[i] != '?')
											{
												card_AI3[i] = row4[i];
												row4[i] = { '?' };
												row4_end = 1;
											}
										}
										row4_end = 1;
									}
									else
									{
										continue;
									}
									break;
								default:
									continue;
								}



								break;
							} 

							//counter++
							for (size_t i = 0; i < 3; i++)
							{
								if (card_AI3[i] == '2')
								{
									counter_AI3[0]++;
								}
								else if (card_AI3[i] == 'S')
								{
									counter_AI3[1]++;
								}
								else if (card_AI3[i] == 'R')
								{
									counter_AI3[2]++;
								}
								else if (card_AI3[i] == 'O')
								{
									counter_AI3[3]++;
								}
								else if (card_AI3[i] == 'Y')
								{
									counter_AI3[4]++;
								}
								else if (card_AI3[i] == 'G')
								{
									counter_AI3[5]++;
								}
								else if (card_AI3[i] == 'B')
								{
									counter_AI3[6]++;
								}
								else if (card_AI3[i] == 'I')
								{
									counter_AI3[7]++;
								}
								else if (card_AI3[i] == 'P')
								{
									counter_AI3[8]++;
								}
								else
								{
									break;
								}

							}

							for (size_t i = 0; i < 3; i++)
							{
								card_AI1[i] = { '0' };
							}

							AI3_end = 1;//AI3 ����
							AI3_have_take_card_end = 1;
					
						}
					}
					if ((row1_end == 1 && row2_end == 1 && row3_end == 1 && row4[2] != '?') || (row1_end == 1 && row2_end == 1 && row4_end == 1 && row3[2] != '?') || (row1_end == 1 && row4_end == 1 && row3_end == 1 && row2[2] != '?') || (row4_end == 1 && row2_end == 1 && row3_end == 1 && row1[2] != '?') || (row1_end == 1 && row2_end == 1 && row3[2] != '?' && row4[2] != '?') || (row1_end == 1 && row3_end == 1 && row2[2] != '?' && row4[2] != '?') || (row1_end == 1 && row4_end == 1 && row3[2] != '?' && row2[2] != '?') || (row3_end == 1 && row2_end == 1 && row1[2] != '?' && row4[2] != '?') || (row4_end == 1 && row2_end == 1 && row3[2] != '?' && row1[2] != '?') || (row3_end == 1 && row4_end == 1 && row1[2] != '?' && row2[2] != '?'))
					{
						card_full_need_select2 = 1;
					}
				}
			}
			
			

			if (row1_end == 1&& row2_end== 1&& row3_end == 1&& row4_end  == 1)
			{			
			round_end = 1;
			cout << "round  just end";//teat
			cout << endl;
			cout << endl;
			cout << endl;
			}
			
			
			
		}

		for (size_t w = 0; w < 75; w++)//�ƳѤU�X�i�P
		{
			if(card_all[w]=='@')
			{
				counter_all_card++;
			}

		}
		if (counter_all_card>=64) //76-4*3
		{
			game_end = 1;
			cout << "game end" << endl;
		}
		else
		{
			counter_all_card = 0;
		}

	}

	//���
	cout << endl;
	cout << "The card that players have amd row have currently" << endl;
	cout << "player:" << ' ' << card[0] << '*' << counter_my[0] << ' ' << card[1] << '*' << counter_my[1] << ' ' << card[2] << '*' << counter_my[2] << ' ' << card[3] << '*' << counter_my[3] << ' ' << card[4] << '*' << counter_my[4] << ' ' << card[5] << '*' << counter_my[5] << ' ' << card[6] << '*' << counter_my[6] << ' ' << card[7] << '*' << counter_my[7] << ' ' << card[8] << '*' << counter_my[8] << endl;
	cout << "AI1:" << ' ' << card[0] << '*' << counter_AI1[0] << ' ' << card[1] << '*' << counter_AI1[1] << ' ' << card[2] << '*' << counter_AI1[2] << ' ' << card[3] << '*' << counter_AI1[3] << ' ' << card[4] << '*' << counter_AI1[4] << ' ' << card[5] << '*' << counter_AI1[5] << ' ' << card[6] << '*' << counter_AI1[6] << ' ' << card[7] << '*' << counter_AI1[7] << ' ' << card[8] << '*' << counter_AI1[8] << endl;
	cout << "AI2:" << ' ' << card[0] << '*' << counter_AI2[0] << ' ' << card[1] << '*' << counter_AI2[1] << ' ' << card[2] << '*' << counter_AI2[2] << ' ' << card[3] << '*' << counter_AI2[3] << ' ' << card[4] << '*' << counter_AI2[4] << ' ' << card[5] << '*' << counter_AI2[5] << ' ' << card[6] << '*' << counter_AI2[6] << ' ' << card[7] << '*' << counter_AI2[7] << ' ' << card[8] << '*' << counter_AI2[8] << endl;
	cout << "AI3:" << ' ' << card[0] << '*' << counter_AI3[0] << ' ' << card[1] << '*' << counter_AI3[1] << ' ' << card[2] << '*' << counter_AI3[2] << ' ' << card[3] << '*' << counter_AI3[3] << ' ' << card[4] << '*' << counter_AI3[4] << ' ' << card[5] << '*' << counter_AI3[5] << ' ' << card[6] << '*' << counter_AI3[6] << ' ' << card[7] << '*' << counter_AI3[7] << ' ' << card[8] << '*' << counter_AI3[8] << endl;
	cout << endl;
	cout << endl;


	//�⦨�Z�o
	int my_Score = score(counter_my);
	int AI1_Score = score(counter_AI1);
	int AI2_Score = score(counter_AI2);
	int AI3_Score = score(counter_AI3);

	cout << "your total score is:" << my_Score <<endl;
	cout << "AI1 total score is:" << AI1_Score << endl;
	cout << "AI2 total score is:" << AI2_Score << endl;
	cout << "AI3 total score is:" << AI3_Score << endl;
	cout << endl; 
	cout << endl;

	//���F�n�P���Z���C

	int everyone_high_to_low_score[4] = { my_Score,AI1_Score ,AI2_Score ,AI3_Score };

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (everyone_high_to_low_score[j] <= everyone_high_to_low_score[j+1])
			{
				int t = everyone_high_to_low_score[j];
				everyone_high_to_low_score[j] = everyone_high_to_low_score[j + 1];
				everyone_high_to_low_score[j + 1] = t;
			}
		}

	}





	//�@��|�W
	cout << "1st is:" ;
	if (everyone_high_to_low_score[0] == my_Score)
	{
		cout << "player"<<endl;
	}
	else if (everyone_high_to_low_score[0] == AI1_Score)
	{
		cout << "AI1" << endl;
	}
	else if (everyone_high_to_low_score[0] == AI2_Score)
	{
		cout << "AI2" << endl;
	}
	else if (everyone_high_to_low_score[0] == AI3_Score)
	{
		cout << "AI3" << endl;
	}


	cout << "2nd is:";
	if (everyone_high_to_low_score[1] == my_Score)
	{
		cout << "player" << endl;
	}
	else if (everyone_high_to_low_score[1] == AI1_Score)
	{
		cout << "AI1" << endl;
	}
	else if (everyone_high_to_low_score[1] == AI2_Score)
	{
		cout << "AI2" << endl;
	}
	else if (everyone_high_to_low_score[1] == AI3_Score)
	{
		cout << "AI3" << endl;
	}


	cout << "3rd is:";
	if (everyone_high_to_low_score[2] == my_Score)
	{
		cout << "player" << endl;
	}
	else if (everyone_high_to_low_score[2] == AI1_Score)
	{
		cout << "AI1" << endl;
	}
	else if (everyone_high_to_low_score[2] == AI2_Score)
	{
		cout << "AI2" << endl;
	}
	else if (everyone_high_to_low_score[2] == AI3_Score)
	{
		cout << "AI3" << endl;
	}


	cout << "4th is:";
	if (everyone_high_to_low_score[3] == my_Score)
	{
		cout << "player" << endl;
	}
	else if (everyone_high_to_low_score[3] == AI1_Score)
	{
		cout << "AI1" << endl;
	}
	else if (everyone_high_to_low_score[3] == AI2_Score)
	{
		cout << "AI2" << endl;
	}
	else if (everyone_high_to_low_score[3] == AI3_Score)
	{
		cout << "AI3" << endl;
	}


	return 0;
}


//���Z��ܩw�q

int score(int counter[])
{
	for (size_t i = 8; i >2; i--)
	{
		for (size_t j = 2; j <8; j++)
		{
			if (counter[j] <= counter[j + 1])
			{
				int t = counter[j];
				counter[j] = counter[j + 1];
				counter[j + 1] = t;
			}
		}

	}



	int sum=0;

	if (counter[1] + counter[2]==1)
	{
		sum = 1;
	}
	else if (counter[1] + counter[2] == 2)
	{
		sum = 3;
	}
	else if (counter[1] + counter[2] == 3)
	{
		sum = 6;
	}
	else if (counter[1] + counter[2] == 4)
	{
		sum = 10;
	}
	else if (counter[1] + counter[2] == 5)
	{
		sum = 15;
	}
	else if ((counter[1] + counter[2] == 6)||(counter[1] + counter[2] == 7)||(counter[1] + counter[2] == 8)||(counter[1] + counter[2] == 9))
	{
		sum = 21;
	}

	/*switch (counter[1]+ counter[2])
	{
	case 1:
		sum = 1;
		break;
	case 2:
		sum = 3;
		break;
	case 3:
		sum = 6;
		break;
	case 4:
		sum = 10;
		break;
	case 5:
		sum = 15;
		break;
	case 6:case 7:case 8: case 9:
		sum = 21;
		break;
	default:
		cout << "error" << endl;
		break;
	}
*/
	switch (counter[3])
	{
	case 1:
		sum += 1;
		break;
	case 2:
		sum += 3;
		break;
	case 3:
		sum += 6;
		break;
	case 4:
		sum += 10;
		break;
	case 5:
		sum += 15;
		break;
	case 6:case 7:case 8: case 9:
		sum += 21;
		break;
	default:
		break;
	}

	switch (counter[4])
	{
	case 1:
		sum += 1;
		break;
	case 2:
		sum += 3;
		break;
	case 3:
		sum += 6;
		break;
	case 4:
		sum += 10;
		break;
	case 5:
		sum += 15;
		break;
	case 6:case 7:case 8: case 9:
		sum += 21;
		break;
	default:
		break;
	}

	switch (counter[5])
	{
	case 1:
		sum -= 1;
		break;
	case 2:
		sum -= 3;
		break;
	case 3:
		sum -= 6;
		break;
	case 4:
		sum -= 10;
		break;
	case 5:
		sum -= 15;
		break;
	case 6:case 7:case 8: case 9:
		sum -= 21;
		break;
	default:
		break;
	}

	switch (counter[6])
	{
	case 1:
		sum -= 1;
		break;
	case 2:
		sum -= 3;
		break;
	case 3:
		sum -= 6;
		break;
	case 4:
		sum -= 10;
		break;
	case 5:
		sum -= 15;
		break;
	case 6:case 7:case 8: case 9:
		sum -= 21;
		break;
	default:
		break;
	}

	switch (counter[7])
	{
	case 1:
		sum -= 1;
		break;
	case 2:
		sum -= 3;
		break;
	case 3:
		sum -= 6;
		break;
	case 4:
		sum -= 10;
		break;
	case 5:
		sum -= 15;
		break;
	case 6:case 7:case 8: case 9:
		sum -= 21;
		break;
	default:
		break;
	}

	switch (counter[8])
	{
	case 1:
		sum -= 1;
		break;
	case 2:
		sum -= 3;
		break;
	case 3:
		sum -= 6;
		break;
	case 4:
		sum -= 10;
		break;
	case 5:
		sum -= 15;
		break;
	case 6:case 7:case 8: case 9:
		sum -= 21;
		break;
	default:
		break;
	}

	sum += (counter[0] * 2);



	return sum;
}