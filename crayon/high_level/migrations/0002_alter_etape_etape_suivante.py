# Generated by Django 4.2.16 on 2024-10-02 15:31

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):
    dependencies = [
        ("high_level", "0001_initial"),
    ]

    operations = [
        migrations.AlterField(
            model_name="etape",
            name="etape_suivante",
            field=models.ForeignKey(
                blank=True,
                null=True,
                on_delete=django.db.models.deletion.PROTECT,
                to="high_level.etape",
            ),
        ),
    ]
