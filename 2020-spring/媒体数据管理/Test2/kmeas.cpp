
#include "kmeas.h"

using namespace std;




int getDistance(Sample pt1, Sample pt2)
{
	return (pt1.x - pt2.x)*(pt1.x - pt2.x) + (pt1.y - pt2.y)*(pt1.y - pt2.y);
}

int getCluster(Sample means[], Sample point)
{
	int temp = 0;
	int label = 0;
	int distance = getDistance(means[0], point);
	vector<Sample> cluster[k];

	for (int i = 1; i < k; i++)
	{
		temp = getDistance(means[i], point);
		if (temp < distance)
		{
			distance = temp;
			label = i;
		}
	}
	return label;
}

Sample getMeans(vector<Sample> cluster) //cluster contains all points in the cluster
{
	float meansX = 0;
	float meansY = 0;
	Sample newMean;
	int num = cluster.size();

	for (int i = 0; i < num; i++)
	{
		meansX += cluster[i].x;
		meansY += cluster[i].y;
	}

	newMean.x = meansX / num;
	newMean.y = meansY / num;

	return newMean;
}

float getVar(vector<Sample> clusters[], Sample means[])
{
	float var = 0;
	for (int i = 0; i < k; i++)
	{
		vector<Sample> pt = clusters[i];
		for (int j = 0; j < pt.size(); j++)
		{
			var += getDistance(pt[j], means[i]);
		}
	}
	return var;
}

void Kmeas(int **data)
{
	Sample means[k];
	vector<Sample> cluster[k];

	for (int i = 0; i < k; i++)
	{
		means[i].x = data[i][0];
		means[i].y = data[i][1];
	}

	Sample pt;
	int label = 0;
	for (int i = 0; i < 11; i++)
	{
		pt.x = data[i][0];
		pt.y = data[i][1];

		label = getCluster(means, pt);
		cout << label<<"  label"<<pt.x <<endl;
		cluster[label].push_back(pt);
	}

	float oldVar = -1;
	float newVar = getVar(cluster, means);

	while (newVar != oldVar)
	{
		for (int i = 0; i < k; i++)
		{
			means[i] = getMeans(cluster[i]);
		}

		oldVar = newVar;
		newVar = getVar(cluster, means);
		for (int i = 0; i < k; i++)
		{
			cluster[i].clear();
		}

		for (int i = 0; i < 11; i++)
		{
			Sample pt;
			pt.x = data[i][0];
			pt.y = data[i][1];

			label = getCluster(means, pt);
			cluster[label].push_back(pt);
			cout << means[i].x << " means[i].x" << pt.x << endl;
		}

		for (label = 0; label < 3; label++)
		{
			cout << "第" << label + 1 << "个簇中的元素是：" << endl;
			vector<Sample> pt;
			pt = cluster[label];

			for (int i = 0; i < pt.size(); i++)
			{
				cout << "(" << pt[i].x << "," << pt[i].y << ")" << "    " << endl;
			}
		}
	}
}
/*int main()
{
	int **data = new int *[11];
	for (int i = 0; i < 11; i++) { data[i] = new int[2]; }
	//Kmeans(data);
	for (int p = 0; p < 11; p++)
	{
		data[p][0] = rand();
		data[p][1] = rand();
	}
	cout << data[3][1];
	//Kmeas(data);
	return 0;
}
*/
